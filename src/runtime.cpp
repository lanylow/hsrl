#include <print>
#include <runtime.hpp>

#include <cstdio>
#include <sstream>
#include <chrono>
#include <print>

#include <hsrl.hpp>
#include <hooks/hooks.hpp>
#include <ui/console.hpp>
#include <lua/lua.hpp>
#include <lua/lauxlib.hpp>
#include <lua/xlua.hpp>

using namespace std::chrono_literals;

static std::string init_script = R"(
local updateCallbacks = { };

hsrl.on_update = function(func)
  table.insert(updateCallbacks, func);
end

hsrl.invoke_update = function()
  for _, func in next, updateCallbacks do
    pcall(func);
  end
end
)";

void runtime::initialize(lua_State* state) {
  std::println("Initializing the lua runtime");
  std::println("HSR state: {}", (void*)state);

  runtime::hsr_state = state;
  runtime::lua_state = luaL_newstate();

  hsrl::open(state);

  runtime::do_buffer(init_script);
}

void runtime::do_buffer(const std::string& source) {
  hooks::loadbuffer.get_trampoline<decltype(&xluaL_loadbuffer)>()(runtime::hsr_state, source.c_str(), source.size(), "hsrl");

  if (lua_pcall(runtime::hsr_state, 0, 0, 0) != LUA_OK)
    lua_pop(runtime::hsr_state, 1);
}
