#pragma once
#include <lua/lstate.hpp>

namespace hsrl {
  int print(lua_State* state);
  int clear(lua_State* state);

  void open(lua_State* state);
}
