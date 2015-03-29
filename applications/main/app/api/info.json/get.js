module.exports = function(client, callback) {
  console.log(client.query);
  
  client.context.data = {
    result: 'OK'
  };
  
  callback();
};
