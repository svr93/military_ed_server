module.exports = function(client, callback) {
  /* to do:
    1) to exclude the loop (need transfer (in single func) a whole array
       instead of elem);
  */

  'use strict';

  var mathLibJS = require(process.cwd() +
    '/applications/main/app/api/info.json/additional_math_funcs.js');
    
  var mathLibCPP = require(process.cwd() +
    '/applications/main/app/api/info.json/build/Release/addon');

  if (!('latitude' in client.query) || !('longitude' in client.query)) {
    client.context.data = {
      err: 'Ошибка запроса'
    };
    
    callback();
    return;
  }

  // uptime() - seconds
  // 1 real second = 100 model seconds

  var currentTime = impress.sandbox.process.uptime() * 100 / (60 * 60 * 24);
  // currentTime: twenty-four hours

  pgsqlConnection.connection.query(
    'SELECT * FROM cstl', function(err, queryResult) {

    if (err) {
      return console.error('error running query', err);
    }

    var station = {
      latitude: +client.query.latitude, // degrees
      longitude: +client.query.longitude // degrees
    };
    
    console.log(station);

    var objArray = queryResult.rows;

    var response = [];

    for (var i = 0; i < objArray.length; ++i) {

      objArray[i].stleccentricity = mathLibJS.getEccentricity(
        objArray[i].stlperigeeh, objArray[i].stlapogeeh);

      objArray[i].stlsemimajoraxis = mathLibJS.getSemiMajorAxis(
        objArray[i].stlperigeeh, objArray[i].stleccentricity); // return: km

      var acc = mathLibCPP.calculateAbsCartesianCoords(
        objArray[i], currentTime);

      var rcc = mathLibCPP.translateAbsCartesianToRelCartesian(
        acc, currentTime);

      var result = mathLibCPP.calculateStationCoords(rcc, station);
      result.stlid = objArray[i].stlid;
      
      result.projection = mathLibCPP.getSatProjection(objArray[i],
                                                      currentTime);

      response.push(result);
    }

    checkReachability(response);
    
  });
  
  function checkReachability(response) {
    
    pgsqlConnection.connection.query(
      'SELECT * FROM cinfotools WHERE \
      infotoolsltd=$1 AND infotoolslng=$2',
      [client.query.latitude, client.query.longitude],
      function(err, queryResult) {

      if (err) {
        return console.error('error running query', err);
      }
      
      var restrictions = queryResult.rows[0];
      
      client.context.data = {
        time: currentTime,
        coords: response.filter(function(elem) {
        
          return (elem.radial_distance *
                  Math.cos(elem.elevation_angle * Math.PI / 180) >
                  (+restrictions.infotoolsminhdist) &&
                  
                  elem.radial_distance *
                  Math.cos(elem.elevation_angle * Math.PI / 180) <
                  (+restrictions.infotoolsmaxhdist) &&
                  
                  elem.radial_distance *
                  Math.sin(elem.elevation_angle * Math.PI / 180) >
                  (+restrictions.infotoolsminvdist) &&
                  
                  elem.radial_distance *
                  Math.sin(elem.elevation_angle * Math.PI / 180) <
                  (+restrictions.infotoolsmaxvdist) &&
                  
                  elem.azimuth_angle >
                  (+restrictions.infotoolsminazangle) &&
                  
                  elem.azimuth_angle <
                  (+restrictions.infotoolsmaxazangle) &&
                  
                  elem.elevation_angle >
                  (+restrictions.infotoolsminelangle) &&
                  
                  elem.elevation_angle <
                  (+restrictions.infotoolsmaxelangle));
                  
        })
      };
      
      callback();
    });
  }
  
};
