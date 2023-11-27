#pragma once

#include "lstate.hpp"

const char* luaL_checklstring(lua_State* state, int index, size_t* len);

int luaL_loadstring(lua_State* state, const char* str);
lua_State* luaL_newstate();

#define luaL_checkstring(state, index) (luaL_checklstring(state, (index), nullptr))