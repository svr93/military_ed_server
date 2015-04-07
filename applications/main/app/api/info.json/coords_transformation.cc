#define BUILDING_NODE_EXTENSION
#include <node.h>

#include <iostream>
#include "math_space.hpp"

using namespace v8;

using std::cout;
using std::endl;

void calculateRC(double& r, double& az, double& eps,
                 double xc, double yc, double zc,
                 double s0, double d0) {
  
  double x0 = 0;
  double y0 = 0;
  double z0 = 0;
  
  get_xyzR_from_sd_grad(s0, d0, 0, x0, y0, z0);
  
  get_RAzEps_from_xyz(r, az, eps, xc, yc, zc, x0, y0, z0, 0, 0, s0, d0);
}

Handle<Value> calculateRelativeCoords(const Arguments& args) {
  HandleScope scope;

  if (args.Length() < 5) {
    ThrowException(Exception::TypeError(String::New("Wrong number of args")));
    return scope.Close(Undefined());
  }

  if (!args[0]->IsNumber() ||
      !args[1]->IsNumber() ||
      !args[2]->IsNumber() ||
      !args[3]->IsNumber() ||
      !args[4]->IsNumber()) {

    ThrowException(Exception::TypeError(String::New("Wrong args")));
    return scope.Close(Undefined());
  }
  
  double r = 0;
  double az = 0;
  double eps = 0;

  double xc = args[0]->NumberValue(); // objX
  double yc = args[1]->NumberValue(); // objY
  double zc = args[2]->NumberValue(); // objZ

  double s0 = args[3]->NumberValue(); // stLatitude
  double d0 = args[4]->NumberValue(); // stLongitude
  
  calculateRC(r, az, eps, xc, yc, zc, s0, d0);

  Local<Object> res = Object::New();
  
  res->Set(String::NewSymbol("radial_distance"), Number::New(r));
  res->Set(String::NewSymbol("azimuth_angle"), Number::New(az));
  res->Set(String::NewSymbol("polar_angle"), Number::New(eps));
  
  return scope.Close(res);
}

Handle<Value> calculateSatellitePos(const Arguments& args) {
  HandleScope scope;

  if (args.Length() < 1) {
    ThrowException(Exception::TypeError(String::New("Wrong number of args")));
    return scope.Close(Undefined());
  }

  if (!args[0]->IsObject()) {
    ThrowException(Exception::TypeError(String::New("Wrong args")));
    return scope.Close(Undefined());
  }

  Local<Object> params = args[0]->ToObject();

  double aosk = params->
    Get(String::NewSymbol("apogee"))->
    NumberValue();

  double e = params->
    Get(String::NewSymbol("perigee"))->
    NumberValue();

  double nakl = params->
    Get(String::NewSymbol("inclination"))->
    NumberValue();

  double dby = params->
    Get(String::NewSymbol("ascendingNodeLongitude"))->
    NumberValue();

  double w = params->
    Get(String::NewSymbol("perigeeArg"))->
    NumberValue();

  double tper = 2 * M_PI * sqrt(pow(aosk, 3) / MU_km_s);

  double t = params->
    Get(String::NewSymbol("currentTime"))->
    NumberValue();

  double D = 0;
  double S = 0;

  cout << "CPP_DEBUG" << endl <<
    "aosk: " << aosk << endl <<
    "e: " << e << endl <<
    "nakl: " << nakl << endl <<
    "dby: " << dby << endl <<
    "w: " << w << endl <<
    "tper: " << tper << endl <<
    "t: " << t << endl <<
    "D: " << D << endl <<
    "S: " << S << endl;

  PodsputnTochka(aosk, e, nakl, dby, w, tper, t, D, S);

  Local<Object> res = Object::New();
  
  res->Set(String::NewSymbol("latitude"), Number::New(S));
  res->Set(String::NewSymbol("longitude"), Number::New(D));

  return scope.Close(res);  
}

void Init(Handle<Object> exports) {

  exports->Set(String::NewSymbol("calculateRelativeCoords"),
               FunctionTemplate::New(calculateRelativeCoords)->
                 GetFunction());

  exports->Set(String::NewSymbol("calculateSatellitePos"),
               FunctionTemplate::New(calculateSatellitePos)->
                 GetFunction());
}

NODE_MODULE(addon, Init)
