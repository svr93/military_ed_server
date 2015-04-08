module.exports = function(client, callback) {

  var mathLib = require(process.cwd() +
  '/applications/main/app/api/info.json/additional_math_funcs.js');
  
  var mathLibCPP = require(process.cwd() +
  '/applications/main/app/api/info.json/build/Release/addon');

  var currentTime = 89.5; // twenty-four hours

  var stLatitude = 0; // degrees
  var stLongitude = 90; // degrees

  var testObject = {
    apogeeHeight: 918.1, // km
    perigeeHeight: 410.2, // km
    inclination: 97.86907, // degrees
    ascendingNodeLongitude: 205.44564, // degrees
    perigeeArg: 29.15896 // degrees
  };

  testObject.eccentricity = mathLib.getEccentricity(testObject.perigeeHeight,
                                                    testObject.apogeeHeight);

  testObject.semiMajorAxis = mathLib.getSemiMajorAxis(testObject.perigeeHeight,
                                                      testObject.eccentricity);

  var acc = mathLibCPP.calculateAbsoluteCartesianCoords(testObject);

  var rcc =
  mathLibCPP.translateAbsoluteCartesianToRelativeCartesian(currentTime,
                                                           acc.x,
                                                           acc.y,
                                                           acc.z);

  var res = mathLibCPP.calculateStationCoords(rcc.x, rcc.y, rcc.z,
                                              stLatitude, stLongitude);

  client.context.data = {
    res: res
  };
  
  callback();
};
