#pragma once

#include "lstate.hpp"

int xluaL_loadbuffer(lua_State* state, const char* chunk, size_t size, const char* name);

int xlua_getglobal(lua_State* state, const char* name);

void xlua_setglobal(lua_State* state, const char* name);
