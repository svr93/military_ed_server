module.exports = function(client, callback) {
  
  var addon = require(process.cwd() +
  '/applications/main/app/api/info.json/build/Release/addon');

  console.log(client.query);
  
  var objX = 6371;
  var objY = 0;
  var objZ = 0;
  
  var stLatitude = 0;
  var stLongitude = 90;
  
  console.log(addon.calculateRelativeCoords(objX, objY, objZ,
                                            stLatitude, stLongitude));

  console.log(addon.calculateSatellitePos({

    apogee: 918.1,
    perigee: 410.2,
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
