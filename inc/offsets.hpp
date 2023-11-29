#pragma once

#include <cstdint>
#include <thread>
#include <windows.h>

using namespace std::chrono_literals;

namespace offsets {
  template <typename type = uintptr_t>
  type get_module(const char* name) {
    return (type)(GetModuleHandleA(name));
  }

  template <typename type = uintptr_t>
  type get_offset(const char* module, const ptrdiff_t offset) {
    return (type)(get_module(module) + offset);
  }

  inline uintptr_t get_exported(const char* module, const char* name) {
    return (uintptr_t)(GetProcAddress(offsets::get_module<HMODULE>(module), name));
  }
}

namespace offsets {
  void initialize();

  inline uintptr_t luaL_checklstring = 0;
  inline uintptr_t luaL_newstate = 0;
  inline uintptr_t luaL_loadstring = 0;

  inline uintptr_t lua_settop = 0;
  inline uintptr_t lua_pushvalue = 0;
  inline uintptr_t lua_type = 0;
  inline uintptr_t lua_tolstring = 0;
  inline uintptr_t lua_pushfstring = 0;
  inline uintptr_t lua_pushcclosure = 0;
  inline uintptr_t lua_getfield = 0;
  inline uintptr_t lua_createtable = 0;
  inline uintptr_t lua_setfield = 0;
  inline uintptr_t lua_pcall = 0;
  inline uintptr_t lua_dump = 0;
  inline uintptr_t lua_error = 0;

  inline uintptr_t xluaL_loadbuffer = 0;
  inline uintptr_t xlua_getglobal = 0;
  inline uintptr_t xlua_setglobal = 0;
}
