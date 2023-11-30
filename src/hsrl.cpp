#include <hsrl.hpp>
#include <ui/console.hpp>
#include <ui/scripts.hpp>
#include <lua/lua.hpp>
#include <lua/lauxlib.hpp>
#include <lua/xlua.hpp>

int hsrl::print(lua_State* state) {
  if (const auto str = luaL_checkstring(state, 1))
    ui::console::add(str);

  return 0;
}

int hsrl::clear([[maybe_unused]] lua_State* state) {
  ui::console::clear();
  return 0;
}

int hsrl::getreg(lua_State* state) {
  lua_pushvalue(state, LUA_REGISTRYINDEX);
  return 1;
}

int hsrl::window::_new(lua_State* state) {
  const auto title = luaL_checkstring(state, 1);

  if (!title)
    return 0;

  const auto window = (ui::scripts::window_t*)(lua_newuserdata(state, sizeof(ui::scripts::window_t)));
  luaL_setmetatable(state, "HSRLWindow");

  new (window) ui::scripts::window_t();
  window->title = title;

  std::unique_lock guard{ ui::scripts::windows_mutex };
  ui::scripts::windows.emplace_back(window);

  return 1;
}

int hsrl::window::settitle(lua_State* state) {
  std::unique_lock guard{ ui::scripts::windows_mutex };

  if (const auto window = (ui::scripts::window_t*)(luaL_checkudata(state, 1 , "HSRLWindow")))
    if (const auto title = luaL_checkstring(state, 2))
      window->title = title;

  return 0;
}

static constexpr luaL_Reg hsrllib[] = {
  { "print", hsrl::print },
  { "clear", hsrl::clear },
  { "getreg", hsrl::getreg },
  { nullptr, nullptr }
};

static constexpr luaL_Reg windowlib[] = {
  { "new", hsrl::window::_new },
  { "settitle", hsrl::window::settitle },
  { nullptr, nullptr }
};

void hsrl::open(lua_State* state) {
  luaL_newlib(state, hsrllib);

  luaL_newmetatable(state, "HSRLWindow");
  luaL_setfuncs(state, windowlib, 0);

  lua_pushvalue(state, -1);
  lua_setfield(state, -2, "__index");

  lua_setfield(state, -2, "window");

  xlua_setglobal(state, "hsrl");
}
