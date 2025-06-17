#include <hsrl.hpp>
#include <ui/console.hpp>
#include <ui/scripts.hpp>
#include <lua/lua.hpp>
#include <lua/lauxlib.hpp>
#include <lua/xlua.hpp>
#include <utils/fnv.hpp>

int hsrl::print(lua_State* state) {
  if (const auto str = luaL_checkstring(state, 1))
    ui::console::add(str);

  return 0;
}

int hsrl::clear(lua_State*) {
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

  const auto window = (ui::scripts::window_t*)lua_newuserdatatagged(state, sizeof(ui::scripts::window_t), 0);
  lua_getfield(state, LUA_REGISTRYINDEX, "HSRLWindow");
  lua_setmetatable(state, -2);

  new(window) ui::scripts::window_t();
  window->title = title;

  std::unique_lock guard{ui::scripts::windows_mutex};
  ui::scripts::windows.emplace_back(window);

  return 1;
}

int hsrl::window::settitle(lua_State* state) {
  std::unique_lock guard{ui::scripts::windows_mutex};

  if (const auto window = (ui::scripts::window_t*)luaL_checkudata(state, 1, "HSRLWindow"))
    if (const auto title = luaL_checkstring(state, 2))
      window->title = title;

  return 0;
}

int hsrl::window::button(lua_State* state) {
  const auto window = (ui::scripts::window_t*)luaL_checkudata(state, 1, "HSRLWindow");
  const auto text = luaL_checkstring(state, 2);
  const auto flag_name = luaL_checkstring(state, 3);

  if (!window || !text || !flag_name)
    return 0;

  ui::scripts::clickable_t::create(window, text, flag_name, ui::scripts::window_object_type::button);

  return 0;
}

int hsrl::window::checkbox(lua_State* state) {
  const auto window = (ui::scripts::window_t*)luaL_checkudata(state, 1, "HSRLWindow");
  const auto text = luaL_checkstring(state, 2);
  const auto flag_name = luaL_checkstring(state, 3);

  if (!window || !text || !flag_name)
    return 0;

  ui::scripts::clickable_t::create(window, text, flag_name, ui::scripts::window_object_type::checkbox);

  return 0;
}

int hsrl::window::sliderint(lua_State* state) {
  const auto window = (ui::scripts::window_t*)luaL_checkudata(state, 1, "HSRLWindow");
  const auto text = luaL_checkstring(state, 2);
  const auto min = luaL_checkinteger(state, 3);
  const auto max = luaL_checkinteger(state, 4);
  const auto flag_name = luaL_checkstring(state, 5);

  if (!window || !text || !flag_name)
    return 0;

  const auto flag = new ui::scripts::flag_t();
  flag->hash = utils::fnv::hash(flag_name);
  flag->type = ui::scripts::flag_type::integer;

  const auto slider = new ui::scripts::slider_t();
  slider->text = text;
  slider->min = (int)(min);
  slider->max = (int)(max);
  slider->flag = flag;
  slider->type = ui::scripts::window_object_type::slider_int;

  flag->object = slider;
  flag->i = (int)(min);

  std::unique_lock guard{ui::scripts::windows_mutex};

  window->objects.emplace_back(slider);
  ui::scripts::flags.emplace_back(flag);

  return 0;
}

int hsrl::getflag(lua_State* state) {
  const auto flag_name = luaL_checkstring(state, 1);

  if (!flag_name)
    return 0;

  const auto flag_hash = utils::fnv::hash(flag_name);

  for (const auto flag : ui::scripts::flags) {
    if (flag->hash != flag_hash)
      continue;

    switch (flag->type) {
    case ui::scripts::flag_type::boolean: {
      lua_pushboolean(state, flag->b);

      if (flag->object->type == ui::scripts::window_object_type::button)
        flag->b = false;

      return 1;
    }

    case ui::scripts::flag_type::integer: {
      lua_pushinteger(state, flag->i);
      return 1;
    }
    }
  }

  return 0;
}

static constexpr luaL_Reg hsrllib[] = {
  {"print", hsrl::print},
  {"clear", hsrl::clear},
  {"getreg", hsrl::getreg},
  {"getflag", hsrl::getflag},
  {nullptr, nullptr}
};

static constexpr luaL_Reg windowlib[] = {
  {"new", hsrl::window::_new},
  {"settitle", hsrl::window::settitle},
  {"button", hsrl::window::button},
  {"checkbox", hsrl::window::checkbox},
  {"sliderint", hsrl::window::sliderint},
  {nullptr, nullptr}
};

void hsrl::setfuncs(lua_State* state, const luaL_Reg* l) {
  for (; l->name != nullptr; l++) {
    lua_pushcfunction(state, l->func);
    lua_setfield(state, -2, l->name);
  }
}

void hsrl::open(lua_State* state) {
  luaL_newlibtable(state, hsrllib);
  hsrl::setfuncs(state, hsrllib);

  luaL_newmetatable(state, "HSRLWindow");
  hsrl::setfuncs(state, windowlib);

  lua_pushvalue(state, -1);
  lua_setfield(state, -2, "__index");

  lua_setfield(state, -2, "window");

  xlua_setglobal(state, "hsrl");
}
