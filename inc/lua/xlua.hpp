#pragma once

#include "lstate.hpp"
#include <offsets.hpp>

DECLARE_METHOD(int, xluaL_loadbuffer, (lua_State* state, const char* chunk, size_t size, const char* name), (state, chunk, size, name));

DECLARE_METHOD(int, xlua_getglobal, (lua_State* state, const char* name), (state, name));

DECLARE_METHOD(void, xlua_setglobal, (lua_State* state, const char* name), (state, name));
