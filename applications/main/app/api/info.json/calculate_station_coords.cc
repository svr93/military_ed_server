#define BUILDING_NODE_EXTENSION

#include "include/calculate_station_coords.hpp"

Handle<Value> calculateStationCoords(const Arguments& args) {
  HandleScope scope;

  if (args.Length() < 2) {
    ThrowException(Exception::TypeError(String::New("Wrong number of args")));
    return scope.Close(Undefined());
  }

  if (!args[0]->IsObject() ||
      !args[1]->IsObject()) {

    ThrowException(Exception::TypeError(String::New("Wrong args")));
    return scope.Close(Undefined());
  }
  
  double r = 0; // km
  double az = 0; // degrees
  double eps = 0; // degrees

  double xc = args[0]->
    Get(String::NewSymbol("x"))->
    NumberValue(); // km

  double yc = args[0]->
    Get(String::NewSymbol("y"))->
    NumberValue(); // km

  double zc = args[0]->
    Get(String::NewSymbol("z"))->
    NumberValue(); // km

  double s0 = args[1]->
    Get(String::NewSymbol("latitude"))->
    NumberValue(); // degrees

  double d0 = args[1]->
    Get(String::NewSymbol("longitude"))->
    NumberValue(); // degrees

  get_RAzEps_from_xyz(r, az, eps, xc, yc, zc, s0, d0);

  Local<Object> res = Object::New();
  
  res->Set(String::NewSymbol("radial_distance"), Number::New(r));
  res->Set(String::NewSymbol("azimuth_angle"), Number::New(az));
  res->Set(String::NewSymbol("elevation_angle"), Number::New(eps));
  
  return scope.Close(res);
}
