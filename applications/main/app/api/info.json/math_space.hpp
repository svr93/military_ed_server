#ifndef _MATH_SPACE_HPP_
#define _MATH_SPACE_HPP_

#include <cmath>

#ifndef M_PI
#define M_PI 3.14
#endif

/* ----- verified constants ----- */

const double pi = M_PI;
const double pi2 = M_PI * 2;

const double fDegreeInRadian = 180.0 / M_PI; // that means degrees in radian
const double fDegreeInGrad = M_PI / 180; // that means radians in degree

const double R_Earth = 6371.0; // Earth radius, [km (SI: m)]
const int Rz = (int)(R_Earth * 1e3); // Earth radius, [m]

const int fSecondsInDay = 60 * 60 * 24;

const double MU_km_s = 3.986e5; // standard gravitational parameter,
                                // [km3 / s2 (SI: m3 / s2)]

const double V_ugl = pi2 / fSecondsInDay; // Earth angular velocity,
                                          // [rad / s, SI]

/* ----- not verified constants ----- */

const double J_1957 = 2436204.5;

const double Mu = MU_km_s * 1e9 * pow((double)fSecondsInDay, 2) /
                                  pow((double)Rz, 3);

/* ----- necessary methods ----- */

void get_xyzR_from_sd_grad(double s, double d, double h,
                           double& x, double& y, double& z);

void get_RAzEps_from_xyz(double& r, double& az, double& eps,
                         double xc, double yc, double zc,
                         double x0, double y0, double z0,
                         double sc, double dc,  // sc, dc are not used
                         double s0, double d0);

void PodsputnTochka(double& aosk, double& e, double& nakl, double& dby,
                    double& w, double& tper, double& t, double& D, double& S);
                         
/* ----- not necessary methods ----- */

double GMST(double t);

double abs_my(double val);

void LBtoGSK(double& dolgota, double& shirota, double& h,
             double& Xgsk, double& Ygsk, double& Zgsk);

void GSKtoNSK(double& Xgsk, double& Ygsk, double& Zgsk,
              double& Xnsk, double& Ynsk, double& Znsk,
              double& t);

#endif
