module.exports = function(client, callback) {
  
  var addon = require(process.cwd() +
  '/applications/main/app/api/info.json/build/Release/addon');

  var mathLib = require(process.cwd() +
  '/applications/main/app/api/info.json/additional_math_funcs.js');

  console.log(client.query);
  
  var objX = 6371; // Earth radius
  var objY = 0;
  var objZ = 0;
  
  var stLatitude = 0;
  var stLongitude = 90;
  
  console.log(addon.calculateRelativeCoords(objX, objY, objZ,
                                            stLatitude, stLongitude));

  var perigeeHeight = 410.2;
  var apogeeHeight = 918.1;

  var eccentricity = mathLib.getEccentricity(perigeeHeight, apogeeHeight);
  var semiMajorAxis = mathLib.getSemiMajorAxis(perigeeHeight, eccentricity);

  console.log(addon.calculateSatellitePos({

    semiMajorAxis: semiMajorAxis,
    eccentricity: eccentricity,
    inclination: 97.86907,
    ascendingNodeLongitude: 205.44564,
    perigeeArg: 29.15896,
    currentTime: 89.5

  })); // only for test; need exclude from get.js
  
  client.context.data = {
    result: 'OK'
  };
  
  callback();
};
