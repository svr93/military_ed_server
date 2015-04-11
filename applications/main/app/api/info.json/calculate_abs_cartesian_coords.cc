#define BUILDING_NODE_EXTENSION

#include "include/calculate_abs_cartesian_coords.hpp"

Handle<Value> calculateAbsCartesianCoords(const Arguments& args) {
  HandleScope scope;

  if (args.Length() < 2) {
    ThrowException(Exception::TypeError(String::New("Wrong number of args")));
    return scope.Close(Undefined());
  }

  if (!args[0]->IsObject() ||
      !args[1]->IsNumber()) {

    ThrowException(Exception::TypeError(String::New("Wrong args")));
    return scope.Close(Undefined());
  }

  double t = args[1]->NumberValue(); // t: twenty-four hours

  double a = args[0]->
    Get(String::NewSymbol("stlsemimajoraxis"))->
    NumberValue(); // a: km

  double e = args[0]->
    Get(String::NewSymbol("stleccentricity"))->
    NumberValue();

  double naklon = args[0]->
    Get(String::NewSymbol("stlincl"))->
    NumberValue(); // naklon: degrees

  double DBY = args[0]->
    Get(String::NewSymbol("stlascendingnodelng"))->
    NumberValue(); // DBY: degrees

  double omega_per = params->
    Get(String::NewSymbol("stlperigeearg"))->
    NumberValue(); // omega_per: degrees

  double tper = 2 * M_PI * sqrt(pow(a, 3) / MU_km_s) / fSecondsInDay;
  // tper: twenty-four hours

  double x = 0; // km
  double y = 0; // km
  double z = 0; // km

  get_ko_xyz_from_t(t, a, e, naklon, DBY, omega_per, tper, x, y, z);

  Local<Object> res = Object::New();
  
  res->Set(String::NewSymbol("x"), Number::New(x));
  res->Set(String::NewSymbol("y"), Number::New(y));
  res->Set(String::NewSymbol("z"), Number::New(z));

  return scope.Close(res);
}
