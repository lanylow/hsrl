#include <lua/lauxlib.hpp>
#include <offsets.hpp>

DECLARE_METHOD(const char*, luaL_checklstring, (lua_State* state, int index, size_t* len), (state, index, len));

DECLARE_METHOD(int, luaL_loadstring, (lua_State* state, const char* str), (state, str));
DECLARE_METHOD(lua_State*, luaL_newstate, (), ());