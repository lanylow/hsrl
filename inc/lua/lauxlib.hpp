#pragma once

#include "lua.hpp"

struct luaL_Reg {
  const char* name;
  void* func;
};

DECLARE_METHOD(const char*, luaL_checklstring, (lua_State* state, int index, size_t* len), (state, index, len));

DECLARE_METHOD(int, luaL_loadstring, (lua_State* state, const char* str), (state, str));
DECLARE_METHOD(lua_State*, luaL_newstate, (), ());

DECLARE_METHOD(void, luaL_setfuncs, (lua_State* state, const luaL_Reg* list, int nup), (state, list, nup));

#define luaL_newlibtable(state, list) lua_createtable(state, 0, sizeof(list) / sizeof((list)[0]) - 1)

#define luaL_newlib(state, list) (luaL_newlibtable(state, list), luaL_setfuncs(state, list, 0))

#define luaL_checkstring(state, index) (luaL_checklstring(state, (index), nullptr))