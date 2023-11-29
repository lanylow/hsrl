#include <runtime.hpp>
#include <hsrl.hpp>
#include <lua/lua.hpp>
#include <lua/lauxlib.hpp>
#include <lua/xlua.hpp>

#include <cstdio>
#include <thread>
#include <sstream>

using namespace std::chrono_literals;

#define register_table(name, members) \
  lua_newtable(state); \
  members \
  xlua_setglobal(state, #name)

#define register_member(name) \
  lua_pushcfunction(state, hsrl::name); \
  lua_setfield(state, -2, #name)

void runtime::initialize(lua_State* state) {
  std::printf("Initializing the lua runtime\n");

  runtime::hsr_state = state;
  runtime::lua_state = luaL_newstate();

  register_table(hsrl,
    register_member(print);
    register_member(clear);
  );
}

void runtime::do_buffer(const std::string& compiled) {
  xluaL_loadbuffer(runtime::hsr_state, compiled.c_str(), compiled.size(), "hsrl");
  lua_pcall(runtime::hsr_state, 0, 0, 0);
}

std::optional<std::string> runtime::compile(const std::string& script) {
  if (luaL_loadstring(runtime::lua_state, script.c_str()) != LUA_OK) {
    const auto error = lua_tostring(runtime::lua_state, 1);
    std::printf("Failed to compile a script: %s\n", error);
    lua_pop(runtime::lua_state, 1);
    return std::nullopt;
  }

  std::ostringstream compiled;

  const auto writer = [](lua_State* state, void* p, size_t s, void* ud) {
    ((std::ostringstream*)(ud))->write((const char*)(p), (std::streamsize)(s));
    return 0;
  };

  lua_dump(runtime::lua_state, writer, &compiled, 0);
  lua_pop(runtime::lua_state, 1);

  return std::make_optional(compiled.str());
}