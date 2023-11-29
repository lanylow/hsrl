#pragma once

#include "lstate.hpp"

#define LUA_OK 0

#define LUA_TSTRING 4

void lua_settop(lua_State* state, int index);
void lua_pushvalue(lua_State* state, int index);

int lua_type(lua_State* state, int index);

const char* lua_tolstring(lua_State* state, int index, size_t* len);

#define lua_pushfstring(state, fmt, ...) ((const char*(*)(lua_State* state, const char*, ...))(offsets::lua_pushfstring))(state, fmt, __VA_ARGS__)
void lua_pushcclosure(lua_State* state, void* func, int nup);

int lua_getfield(lua_State* state, int index, const char* name);
void lua_createtable(lua_State* state, int narr, int nrec);

void lua_setfield(lua_State* state, int index, const char* name);

int lua_pcall(lua_State* state, int nargs, int nresults, int errfunc);
int lua_dump(lua_State* state, int(*writer)(lua_State*, void*, size_t, void*), void* data, int strip);

#define lua_pop(state, amount) lua_settop(state, -(amount) - 1)

#define lua_newtable(state) lua_createtable(state, 0, 0)

#define lua_pushcfunction(state, func) lua_pushcclosure(state, (func), 0)

#define lua_tostring(state, index) lua_tolstring(state, (index), nullptr)