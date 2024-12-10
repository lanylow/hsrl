#pragma once

#include <lua/lstate.hpp>
#include <lua/lauxlib.hpp>

namespace hsrl {
  int print(lua_State* state);
  int clear(lua_State* state);
  int getreg(lua_State* state);

  namespace window {
    int _new(lua_State* state);
    int settitle(lua_State* state);
    int button(lua_State* state);
    int checkbox(lua_State* state);
    int sliderint(lua_State* state);
  }

  int getflag(lua_State* state);

  void setfuncs(lua_State* state, const luaL_Reg* l);
  void open(lua_State* state);
}
