#include <hsrl.hpp>
#include <lua/lua.hpp>
#include <lua/lauxlib.hpp>

#include <cstdio>

int hsrl::print(lua_State* state) {
  std::printf("%s\n", luaL_checkstring(state, 1));
  return 0;
}
