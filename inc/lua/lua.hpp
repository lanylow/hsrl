#pragma once

#include "lstate.hpp"
#include <offsets.hpp>

#define LUA_REGISTRYINDEX	(-10000)

#define LUA_OK 0

#define LUA_TSTRING 5

DECLARE_METHOD(void, lua_settop, (lua_State* state, int index), (state, index));
DECLARE_METHOD(void, lua_pushvalue, (lua_State* state, int index), (state, index));

DECLARE_METHOD(int, lua_type, (lua_State* state, int index), (state, index));

DECLARE_METHOD(const char*, lua_tolstring, (lua_State* state, int index, size_t* len), (state, index, len));

DECLARE_METHOD(void, lua_pushinteger, (lua_State* state, long long val), (state, val));
DECLARE_METHOD(void, lua_pushcclosurek, (lua_State* state, void* func, const char* debug_name, int nup, void* cont), (state, func, debug_name, nup, cont));
DECLARE_METHOD(void, lua_pushboolean, (lua_State* state, int val), (state, val));

DECLARE_METHOD(int, lua_getfield, (lua_State* state, int index, const char* name), (state, index, name));
DECLARE_METHOD(void, lua_createtable, (lua_State* state, int narr, int nrec), (state, narr, nrec));
DECLARE_METHOD(void*, lua_newuserdatatagged, (lua_State* state, size_t size, int tag), (state, size, tag));

DECLARE_METHOD(void, lua_setfield, (lua_State* state, int index, const char* name), (state, index, name));
DECLARE_METHOD(void, lua_setmetatable, (lua_State* state, int index), (state, index));

DECLARE_METHOD(int, lua_pcall, (lua_State* state, int nargs, int nresults, int errfunc), (state, nargs, nresults, errfunc));

#define lua_pop(state, amount) lua_settop(state, -(amount) - 1)

#define lua_pushcfunction(state, func) lua_pushcclosurek(state, (func), "", 0, nullptr)

#define lua_tostring(state, index) lua_tolstring(state, (index), nullptr)
