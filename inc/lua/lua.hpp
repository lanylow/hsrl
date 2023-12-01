#pragma once

#include "lstate.hpp"
#include "luaconf.hpp"
#include <offsets.hpp>

#define LUA_REGISTRYINDEX	(-LUAI_MAXSTACK - 1000)

#define LUA_OK 0

#define LUA_TSTRING 4

DECLARE_METHOD(void, lua_settop, (lua_State* state, int index), (state, index));
DECLARE_METHOD(void, lua_pushvalue, (lua_State* state, int index), (state, index));

DECLARE_METHOD(int, lua_type, (lua_State* state, int index), (state, index));

DECLARE_METHOD(const char*, lua_tolstring, (lua_State* state, int index, size_t* len), (state, index, len));

#define lua_pushfstring(state, fmt, ...) ((const char*(*)(lua_State* state, const char*, ...))(offsets::lua_pushfstring))(state, fmt, __VA_ARGS__)
DECLARE_METHOD(void, lua_pushcclosure, (lua_State* state, void* func, int nup), (state, func, nup));
DECLARE_METHOD(void, lua_pushboolean, (lua_State* state, int val), (state, val));

DECLARE_METHOD(int, lua_getfield, (lua_State* state, int index, const char* name), (state, index, name));
DECLARE_METHOD(void, lua_createtable, (lua_State* state, int narr, int nrec), (state, narr, nrec));
DECLARE_METHOD(void*, lua_newuserdata, (lua_State* state, size_t size), (state, size));

DECLARE_METHOD(void, lua_setfield, (lua_State* state, int index, const char* name), (state, index, name));

DECLARE_METHOD(int, lua_pcall, (lua_State* state, int nargs, int nresults, int errfunc), (state, nargs, nresults, errfunc));
DECLARE_METHOD(int, lua_dump, (lua_State* state, int(*writer)(lua_State*, void*, size_t, void*), void* data, int strip), (state, writer, data, strip));

#define lua_pop(state, amount) lua_settop(state, -(amount) - 1)

#define lua_newtable(state) lua_createtable(state, 0, 0)

#define lua_pushcfunction(state, func) lua_pushcclosure(state, (func), 0)

#define lua_tostring(state, index) lua_tolstring(state, (index), nullptr)