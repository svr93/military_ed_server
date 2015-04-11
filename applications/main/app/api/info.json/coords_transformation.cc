#define BUILDING_NODE_EXTENSION

#include <node.h>

#include "include/calculate_abs_cartesian_coords.hpp"
#include "include/translate_abs_cartesian_to_rel_cartesian.hpp"
#include "include/calculate_station_coords.hpp"

using namespace v8;

void Init(Handle<Object> exports) {

  exports->Set(String::NewSymbol("calculateAbsCartesianCoords"),
               FunctionTemplate::New(calculateAbsCartesianCoords)->
                 GetFunction());

  exports->Set(String::NewSymbol("translateAbsCartesianToRelCartesian"),
               FunctionTemplate::New(translateAbsCartesianToRelCartesian)->
                 GetFunction());

  exports->Set(String::NewSymbol("calculateStationCoords"),
               FunctionTemplate::New(calculateStationCoords)->
                 GetFunction());
}

NODE_MODULE(addon, Init)
