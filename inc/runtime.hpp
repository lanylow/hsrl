#pragma once

#include <lua/lstate.hpp>

#include <optional>
#include <string>

namespace runtime {
  void initialize(lua_State* state);

  void do_buffer(const std::string& compiled);
  std::optional<std::string> compile(const std::string& script);

  inline lua_State* lua_state;
  inline lua_State* hsr_state;
}