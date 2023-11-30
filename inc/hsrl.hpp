#pragma once

#include <lua/lstate.hpp>

namespace hsrl {
  int print(lua_State* state);
  int clear(lua_State* state);
  int getreg(lua_State* state);

  namespace window {
    int _new(lua_State* state);
    int settitle(lua_State* state);
  }

  void open(lua_State* state);
}
