'use strict';

var EARTH_RADIUS = 6371.0; // Earth average radius [km (SI: m)]

exports.getEccentricity = function(perigeeHeight, apogeeHeight) {
  // perigeeHeight, apogeeHeight: km

  // see https://ru.wikipedia.org/wiki/Апоцентр_и_перицентр
  // perigeeRadius = perigeeHeight + EARTH_RADIUS

  var eccentricity = (apogeeHeight - perigeeHeight) /
                     (2 * EARTH_RADIUS + apogeeHeight + perigeeHeight);

  return eccentricity;
};

exports.getSemiMajorAxis = function(perigeeHeight, eccentricity) {
  // perigeeHeight: km, return: km

  return (EARTH_RADIUS + perigeeHeight) / (1 - eccentricity);
};

exports.translateRelativeCartesianToGeographic = function(x, y, z) {
  // x, y, z: km, return: degrees, km

  var radial_distance = Math.sqrt(x * x + y * y + z * z);
  var polar_angle = Math.atan(Math.sqrt(x * x + y * y) / z);
  var azimuthal_angle = Math.atan(y / x);

  if (isNaN(azimuthal_angle)) {
    azimuthal_angle = 0;
  }

  var latitudeRad = Math.abs(Math.PI - polar_angle) - Math.PI / 2;

  var longitudeRad = (azimuthal_angle < 2 * Math.PI) ?
                  azimuthal_angle : azimuthal_angle - 2 * Math.PI;

  return {
    latitude: latitudeRad * 180 / Math.PI,
    longitude: longitudeRad * 180 / Math.PI,
    height: radial_distance - EARTH_RADIUS,
  };

};
