#pragma once

#include <d3d11.h>
#include <lua/lua.hpp>

namespace hooks::endpoints {
  long __stdcall present(IDXGISwapChain* swap_chain, unsigned int sync_interval, unsigned int flags);
  long __stdcall resize_buffers(IDXGISwapChain* swap_chain, unsigned int buffer_count, unsigned int width, unsigned int height, DXGI_FORMAT format, unsigned int flags);
  long long __stdcall wndproc(HWND window, unsigned int message, unsigned long long wparam, long long lparam);
  int loadbuffer(lua_State* state, const char* chunk, size_t size, const char* name);
  int error(lua_State* state);
  void update(void* __this);
}