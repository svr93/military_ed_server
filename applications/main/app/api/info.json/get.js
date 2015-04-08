module.exports = function(client, callback) {

  var mathLib = require(process.cwd() +
  '/applications/main/app/api/info.json/additional_math_funcs.js');
  
  var mathLibCPP = require(process.cwd() +
  '/applications/main/app/api/info.json/build/Release/addon');
  
  var objX = 6371; // Earth radius, km
  var objY = 0;
  var objZ = 0;
  
  var stLatitude = 0;
  var stLongitude = 90; // degrees
  
  console.log(mathLibCPP.calculateStationCoords(objX, objY, objZ,
                                            stLatitude, stLongitude));

  var perigeeHeight = 410.2; // km
  var apogeeHeight = 918.1;  // km

  var eccentricity = mathLib.getEccentricity(perigeeHeight, apogeeHeight);
  var semiMajorAxis = mathLib.getSemiMajorAxis(perigeeHeight, eccentricity);
//00
  console.log(mathLibCPP.calculateRelativeCartesianCoords({

    currentTime: 89.5,
    semiMajorAxis: semiMajorAxis,
    eccentricity: eccentricity,
    inclination: 97.86907,
    ascendingNodeLongitude: 205.44564,
    perigeeArg: 29.15896

  }));
//0  
  client.context.data = {
    result: 'OK'
  };
  
  callback();
};
