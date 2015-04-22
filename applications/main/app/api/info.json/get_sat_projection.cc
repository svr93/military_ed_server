#define BUILDING_NODE_EXTENSION

#include "include/get_sat_projection.hpp"

Handle<Value> getSatProjection(const Arguments& args) {
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

  double t = (args[1]->NumberValue()) * fSecondsInDay; // t: seconds

  Local<Object> stl = args[0]->ToObject();

  double aosk = stl->
    Get(String::NewSymbol("stlsemimajoraxis"))->
    NumberValue(); // aosk: km

  double e = stl->
    Get(String::NewSymbol("stleccentricity"))->
    NumberValue();

  double nakl = (stl->
    Get(String::NewSymbol("stlincl"))->
    NumberValue()) * fDegreeInGrad; // nakl: radians

  double dby = (stl->
    Get(String::NewSymbol("stlascendingnodelng"))->
    NumberValue()) * fDegreeInGrad; // dby: radians

  double w = (stl->
    Get(String::NewSymbol("stlperigeearg"))->
    NumberValue()) * fDegreeInGrad; // w: radians

  double tper = 2 * M_PI * sqrt(pow(aosk, 3) / MU_km_s) / fSecondsInDay;
  // tper: twenty-four hours

  double D = 0; // radians
  double S = 0; // radians
  
  PodsputnTochka(aosk, e, nakl, dby, w, tper, t, D, S);
  
  if (D > M_PI) {
    D -= 2 * M_PI;
  }

  Local<Object> res = Object::New();
  
  res->Set(String::NewSymbol("latitude"),
           Number::New(S * fDegreeInRadian));
           
  res->Set(String::NewSymbol("longitude"),
           Number::New(D * fDegreeInRadian));  

  return scope.Close(res);
}
