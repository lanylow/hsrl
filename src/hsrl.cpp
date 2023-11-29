#include <hsrl.hpp>
#include <ui/console.hpp>
#include <lua/lua.hpp>
#include <lua/lauxlib.hpp>

#include <mutex>

int hsrl::print(lua_State* state) {
  std::unique_lock guard{ ui::console::lines_mutex };

  if (auto str = luaL_checkstring(state, 1))
    ui::console::lines.emplace_back(str);

  return 0;
}

int hsrl::clear([[maybe_unused]] lua_State* state) {
  std::unique_lock guard{ ui::console::lines_mutex };
  ui::console::lines.clear();
  return 0;
}