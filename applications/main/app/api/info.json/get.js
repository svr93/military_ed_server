module.exports = function(client, callback) {
  console.log(client.query);

  pgsqlConnection.connection.query( // only for test
    'SELECT * FROM satellites', function(err, result) {

    if (err) {
      return console.error('error running query', err);
    }

    console.log(result.rows);
  });

  var mathLib = require(process.cwd() +
  '/applications/main/app/api/info.json/additional_math_funcs.js');
  
  var mathLibCPP = require(process.cwd() +
  '/applications/main/app/api/info.json/build/Release/addon');

  var currentTime = 89.5; // twenty-four hours

  if (!('latitude' in client.query) || !('longitude' in client.query)) {
    client.context.data = {
      err: 'Ошибка запроса'
    };
  
    callback();
    return;
  }

  var stLatitude = +client.query.latitude; // degrees
  var stLongitude = +client.query.longitude; // degrees

  var testObject = {
    apogeeHeight: 918.1, // km
    perigeeHeight: 410.2, // km
    inclination: 97.86907, // degrees
    ascendingNodeLongitude: 205.44564, // degrees
    perigeeArg: 29.15896, // degrees
    currentTime: currentTime // need exclude
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
