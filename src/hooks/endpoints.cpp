#include <hooks/hooks.hpp>
#include <hooks/endpoints.hpp>
#include <runtime.hpp>
#include <ui/ui.hpp>
#include <ui/menu.hpp>
#include <ui/console.hpp>
#include <ui/scripts.hpp>
#include <lua/lua.hpp>

#include <intrin.h>

#pragma warning(disable: 6387)

long __stdcall hooks::endpoints::present(IDXGISwapChain* swap_chain, unsigned int sync_interval, unsigned int flags) {
  utils::call_once(hooks::present.storage.init_flag, [&] {
    swap_chain->GetDevice(__uuidof(ID3D11Device), (void**)(&hooks::present.storage.device));
    hooks::present.storage.device->GetImmediateContext(&hooks::present.storage.context);

    DXGI_SWAP_CHAIN_DESC swap_chain_desc;
    swap_chain->GetDesc(&swap_chain_desc);
    hooks::wndproc.storage.window = swap_chain_desc.OutputWindow;
    hooks::wndproc.set_trampoline(SetWindowLongPtrA(hooks::wndproc.storage.window, GWLP_WNDPROC, (long long)(hooks::endpoints::wndproc)));

    ui::initialize();
  });

  utils::call_once(hooks::present.storage.render_target_flag, [&] {
    ID3D11Texture2D* back_buffer;
    swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)(&back_buffer));
    hooks::present.storage.device->CreateRenderTargetView(back_buffer, nullptr, &hooks::present.storage.render_target);
    back_buffer->Release();
  });

  ui::begin();
  ui::menu::render();
  ui::console::render();
  ui::scripts::render();
  ui::end();

  return hooks::present.get_trampoline<decltype(&hooks::endpoints::present)>()(swap_chain, sync_interval, flags);
}

#pragma warning(default: 6387)

long __stdcall hooks::endpoints::resize_buffers(IDXGISwapChain* swap_chain, unsigned int buffer_count, unsigned int width, unsigned int height, DXGI_FORMAT format, unsigned int flags) {
  hooks::present.storage.render_target->Release();
  hooks::present.storage.render_target = nullptr;
  hooks::present.storage.render_target_flag.reset();

  return hooks::resize_buffers.get_trampoline<decltype(&hooks::endpoints::resize_buffers)>()(swap_chain, buffer_count, width, height, format, flags);
}

long long __stdcall hooks::endpoints::wndproc(HWND hwnd, unsigned int message, unsigned long long wparam, long long lparam) {
  if (!ui::handle_message(hwnd, message, wparam, lparam) && ui::menu::opened)
    return true;

  return CallWindowProcA(hooks::wndproc.get_trampoline<decltype(&hooks::endpoints::wndproc)>(), hwnd, message, wparam, lparam);
}

int hooks::endpoints::loadbuffer(lua_State* state, const char* chunk, size_t size, const char* name) {
  utils::call_once(hooks::loadbuffer.storage.init_flag, [&] {
    hooks::present.install_swap_chain(8, &hooks::endpoints::present);
    hooks::resize_buffers.install_swap_chain(13, &hooks::endpoints::resize_buffers);

    runtime::initialize(state);
  });

  return hooks::loadbuffer.get_trampoline<decltype(&hooks::endpoints::loadbuffer)>()(state, chunk, size, name);
}

int hooks::endpoints::error(lua_State* state) {
  if (lua_type(state, -1) == LUA_TSTRING)
    if (const auto str = lua_tostring(state, -1))
      ui::console::add(str);

  return hooks::error.get_trampoline<decltype(&hooks::endpoints::error)>()(state);
}