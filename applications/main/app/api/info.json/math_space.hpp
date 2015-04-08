#ifndef _MATH_SPACE_HPP_
#define _MATH_SPACE_HPP_

#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265
#endif

/* ----- verified constants ----- */

const double pi = M_PI;
const double pi2 = M_PI * 2;

const double fDegreeInRadian = 180.0 / M_PI; // that means degrees in radian
const double fDegreeInGrad = M_PI / 180; // that means radians in degree

const double R_Earth = 6371.0; // Earth average radius [km (SI: m)]
const int Rz = (int)(R_Earth * 1e3); // Earth average radius [m]

const int fSecondsInDay = 60 * 60 * 24; // seconds in twenty-four hours

const double MU_km_s = 398600.4418; // standard gravitational parameter
                                    // [km3 / s2 (SI: m3 / s2)]

const double Mu = MU_km_s;

const double V_ugl = pi2 / fSecondsInDay; // Earth angular velocity
                                          // [rad / s, SI]

const double J_1957 = 2435839.5; // Julian date (01.01.1957)
                                 // [twenty-four hours]
// http://www.astronet.ru/db/msg/1190817/node36.html

/* ----- necessary methods ----- */

void get_xyzR_from_sd_grad(double s, double d, // s, d: degrees
                           double h, // h is not used
                           double& x, double& y, double& z); // x, y, z: km

void get_RAzEps_from_xyz(double& r, double& az, double& eps, // r: km,
                                                             // az: degrees,
                                                             // eps: degrees
                         double xc, double yc, double zc, // xc, yc, zc: km
                         double x0, double y0, double z0, // x0, y0, z0: km
                         double sc, double dc,  // sc, dc are not used
                         double s0, double d0); // s0, d0: degrees

void PodsputnTochka(double& aosk, double& e, // aosk: km
                    double& nakl, double& dby, // nakl, dby: radians
                    double& w, // w: radians
                    double& tper, double& t, // tper, t: twenty-four hours
                    double& D, double& S); // D, S: radians
                         
/* ----- not necessary methods ----- */

double GMST(double t); // t: twenty-four hours; return: radians

double abs_my(double val);

void LBtoGSK(double& dolgota, double& shirota, double& h,
             double& Xgsk, double& Ygsk, double& Zgsk);

void GSKtoNSK(double& Xgsk, double& Ygsk, double& Zgsk,
              double& Xnsk, double& Ynsk, double& Znsk,
              double& t);

#endif
