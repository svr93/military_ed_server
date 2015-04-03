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
  
  client.context.data = {
    result: 'OK'
  };
  
  callback();
};
