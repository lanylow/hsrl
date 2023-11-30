#include <hsrl.hpp>
#include <ui/console.hpp>
#include <lua/lua.hpp>
#include <lua/lauxlib.hpp>
#include <lua/xlua.hpp>

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

static constexpr luaL_Reg hsrllib[] = {
  { "print", hsrl::print },
  { "clear", hsrl::clear },
  { nullptr, nullptr }
};

void hsrl::open(lua_State* state) {
  luaL_newlib(state, hsrllib);
  xlua_setglobal(state, "hsrl");
}
