#pragma once

#include <lua/lstate.hpp>

#include <string>

namespace runtime {
  void initialize(lua_State* state);
  void do_buffer(const std::string& source);

  inline lua_State* lua_state;
  inline lua_State* hsr_state;
}
