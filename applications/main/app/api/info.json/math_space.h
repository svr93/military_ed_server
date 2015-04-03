#ifndef _MATH_SPACE_H_
#define _MATH_SPACE_H_

#include <math.h>

#define pi M_PI
#define pi2 (M_PI * 2)
#define fDegreeInRadian (180.0/M_PI)
#define fDegreeInGrad (M_PI/180.0)
#define R_Earth 6371
#define fSecondsInDay 86400.0
#define V_ugl (M_PI * 2.0 / fSecondsInDay)
#define J_1957 2436204.5
#define Rz (R_Earth * 1000)
#define Mu (398600.44e9 * pow(fSecondsInDay, 2.0) / pow(Rz, 3.0))
#define MU_km_s 398600.44

double GMST(double t);
double abs_my(double val);

void LBtoGSK(double& dolgota, double& shirota,
double& h, double& Xgsk,double& Ygsk,double& Zgsk);

void GSKtoNSK(double & Xgsk, double & Ygsk, double & Zgsk,
double & Xnsk, double & Ynsk, double & Znsk, double& t);

/* ----- necessary methods ----- */

void get_xyzR_from_sd_grad(double s, double d, double h,
double& x, double& y, double& z);

void get_RAzEps_from_xyz(double& r, double& az, double& eps,
double xc, double yc, double zc,
double x0, double y0, double z0,
double sc, double dc,
double s0, double d0);

#endif
