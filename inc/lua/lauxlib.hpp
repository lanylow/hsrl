#pragma once

#include "lua.hpp"

struct luaL_Reg {
  const char* name;
  void* func;
};

DECLARE_METHOD(const char*, luaL_checklstring, (lua_State* state, int index, size_t* len), (state, index, len));
DECLARE_METHOD(long long, luaL_checkinteger, (lua_State* state, int index), (state, index));

DECLARE_METHOD(void, luaL_newmetatable, (lua_State* state, const char* name), (state, name));
DECLARE_METHOD(void*, luaL_checkudata, (lua_State* state, int index, const char* name), (state, index, name));

DECLARE_METHOD(int, luaL_loadstring, (lua_State* state, const char* str), (state, str));
DECLARE_METHOD(lua_State*, luaL_newstate, (), ());

#define luaL_newlibtable(state, list) lua_createtable(state, 0, sizeof(list) / sizeof((list)[0]) - 1)

#define luaL_checkstring(state, index) (luaL_checklstring(state, (index), nullptr))
