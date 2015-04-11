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

  Local<Object> stl = args[0]->ToObject();

  double xc = stl->
    Get(String::NewSymbol("x"))->
    NumberValue(); // km

  double yc = stl->
    Get(String::NewSymbol("y"))->
    NumberValue(); // km

  double zc = stl->
    Get(String::NewSymbol("z"))->
    NumberValue(); // km

  Local<Object> station = args[1]->ToObject();

  double s0 = station->
    Get(String::NewSymbol("latitude"))->
    NumberValue(); // degrees

  double d0 = station->
    Get(String::NewSymbol("longitude"))->
    NumberValue(); // degrees

  get_RAzEps_from_xyz(r, az, eps, xc, yc, zc, s0, d0);

  Local<Object> res = Object::New();
  
  res->Set(String::NewSymbol("radial_distance"), Number::New(r));
  res->Set(String::NewSymbol("azimuth_angle"), Number::New(az));
  res->Set(String::NewSymbol("elevation_angle"), Number::New(eps));
  
  return scope.Close(res);
}
