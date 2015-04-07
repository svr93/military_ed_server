exports.getEccentricity = function(Rper, Rapog) {
  // see https://ru.wikipedia.org/wiki/Апоцентр_и_перицентр

  var k = Rper / Rapog;
  return (1 - k) / (1 + k);
};

exports.getSemiMajorAxis = function(Rper, eccentricity) {
  // see https://ru.wikipedia.org/wiki/Апоцентр_и_перицентр

  return Rper / (1 - eccentricity);
};
