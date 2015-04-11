#define BUILDING_NODE_EXTENSION

#include "include/translate_abs_cartesian_to_rel_cartesian.hpp"

Handle<Value> translateAbsCartesianToRelCartesian(const Arguments& args) {
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

  Local<Object> stl = args[0]->ToObject();

  double x = stl->
    Get(String::NewSymbol("x"))->
    NumberValue(); // km

  double y = stl->
    Get(String::NewSymbol("y"))->
    NumberValue(); // km

  double z = stl->
    Get(String::NewSymbol("z"))->
    NumberValue(); // km

  double x_z = 0; // km
  double y_z = 0; // km
  double z_z = 0; // km

  get_Zxyz_from_xyz(t, x, y, z, x_z, y_z, z_z);

  Local<Object> res = Object::New();
  
  res->Set(String::NewSymbol("x"), Number::New(x_z));
  res->Set(String::NewSymbol("y"), Number::New(y_z));
  res->Set(String::NewSymbol("z"), Number::New(z_z));

  return scope.Close(res);  
}
