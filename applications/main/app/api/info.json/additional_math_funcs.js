'use strict';

var EARTH_RADIUS = 6371.0; // [km (SI: m)]

exports.getEccentricity = function(perigeeHeight, apogeeHeight) {
  // see https://ru.wikipedia.org/wiki/Апоцентр_и_перицентр
  // perigeeRadius = perigeeHeight + EARTH_RADIUS

  var eccentricity = (apogeeHeight - perigeeHeight) /
                     (2 * EARTH_RADIUS + apogeeHeight + perigeeHeight);

  return eccentricity;
};

exports.getSemiMajorAxis = function(perigeeHeight, eccentricity) {
  // see https://ru.wikipedia.org/wiki/Апоцентр_и_перицентр
  // perigeeRadius = perigeeHeight + EARTH_RADIUS

  return (EARTH_RADIUS + perigeeHeight) / (1 - eccentricity);
};
