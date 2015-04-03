#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "math_space.h"

using namespace v8;

void calculate(double& r, double& az, double& eps,
double xc, double yc, double zc, double s0, double d0) {
  
  double x0 = 0;
  double y0 = 0;
  double z0 = 0;
  
  get_xyzR_from_sd_grad(s0, d0, 0, x0, y0, z0);
  
  get_RAzEps_from_xyz(r, az, eps, xc, yc, zc, x0, y0, z0, 0, 0, s0, d0);
}  

Handle<Value> calculateRelativeCoords(const Arguments& args) {
  HandleScope scope;

  if (args.Length() < 5) {
    ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
    return scope.Close(Undefined());
  }

  if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
    ThrowException(Exception::TypeError(String::New("Wrong arguments")));
    return scope.Close(Undefined());
  }
  
  double r = 0;
  double az = 0;
  double eps = 0;
  
  calculate(r, az, eps,
  args[0]->NumberValue(),
  args[1]->NumberValue(),
  args[2]->NumberValue(),
  args[3]->NumberValue(),
  args[4]->NumberValue()); 

  Local<Object> obj = Object::New();
  
  obj->Set(String::NewSymbol("r"), Number::New(r));
  obj->Set(String::NewSymbol("az"), Number::New(az));
  obj->Set(String::NewSymbol("eps"), Number::New(eps));
  
  return scope.Close(obj);
}

void Init(Handle<Object> exports) {
  exports->Set(String::NewSymbol("calculateRelativeCoords"),
      FunctionTemplate::New(calculateRelativeCoords)->GetFunction());
}

NODE_MODULE(addon, Init)
