#include <hsrl.hpp>
#include <menu.hpp>
#include <lua/lua.hpp>
#include <lua/lauxlib.hpp>

#include <mutex>

int hsrl::print(lua_State* state) {
  std::unique_lock guard{ menu::lines_mutex };

  if (auto str = luaL_checkstring(state, 1))
    menu::lines.emplace_back(str);

  return 0;
}

int hsrl::clear([[maybe_unused]] lua_State* state) {
  std::unique_lock guard{ menu::lines_mutex };
  menu::lines.clear();
  return 0;
}