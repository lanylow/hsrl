#include <lua/lua.hpp>
#include <offsets.hpp>

DECLARE_METHOD(void, lua_settop, (lua_State* state, int index), (state, index));
DECLARE_METHOD(void, lua_pushvalue, (lua_State* state, int index), (state, index));

DECLARE_METHOD(int, lua_type, (lua_State* state, int index), (state, index));

DECLARE_METHOD(const char*, lua_tolstring, (lua_State* state, int index, size_t* len), (state, index, len));

DECLARE_METHOD(void, lua_pushcclosure, (lua_State* state, void* func, int nup), (state, func, nup));

DECLARE_METHOD(int, lua_getfield, (lua_State* state, int index, const char* name), (state, index, name));
DECLARE_METHOD(void, lua_createtable, (lua_State* state, int narr, int nrec), (state, narr, nrec));

DECLARE_METHOD(void, lua_setfield, (lua_State* state, int index, const char* name), (state, index, name));

DECLARE_METHOD(int, lua_pcall, (lua_State* state, int nargs, int nresults, int errfunc), (state, nargs, nresults, errfunc));
DECLARE_METHOD(int, lua_dump, (lua_State* state, int(*writer)(lua_State*, void*, size_t, void*), void* data, int strip), (state, writer, data, strip));