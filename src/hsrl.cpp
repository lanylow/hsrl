#include <hsrl.hpp>
#include <ui/console.hpp>
#include <lua/lua.hpp>
#include <lua/lauxlib.hpp>

#include <mutex>

int hsrl::print(lua_State* state) {
  if (const auto str = luaL_checkstring(state, 1))
    ui::console::add(str);

  return 0;
}

int hsrl::clear([[maybe_unused]] lua_State* state) {
  ui::console::clear();
  return 0;
}