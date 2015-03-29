// URL rewriting and request forwarding rules

module.exports = [

  {
    url: '/(info|kill)((\?)(.*)|)',
    rewrite: '/api/[1].json[2]'
  }
  
];
