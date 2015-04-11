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

      response.push(result);
    }

    client.context.data = response;
    callback();
    
  });
};
