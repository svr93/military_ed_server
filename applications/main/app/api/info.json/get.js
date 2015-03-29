module.exports = function(client, callback) {
  
  var addon = require(process.cwd() +
  '/applications/main/app/api/info.json/build/Release/addon');

  console.log(client.query);
  
  console.log(addon.add(7, 11));
  
  client.context.data = {
    result: 'OK'
  };
  
  callback();
};
