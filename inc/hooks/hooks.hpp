#pragma once

#include <utils/once.hpp>
#include <hooks/hook.hpp>

#include <d3d11.h>

namespace hooks {
  struct present_storage : hooks::hook_storage {
    ID3D11Device* device{nullptr};
    ID3D11DeviceContext* context{nullptr};
    ID3D11RenderTargetView* render_target{nullptr};

    utils::once_flag init_flag;
    utils::once_flag render_target_flag;
  };

  struct wndproc_storage : hooks::hook_storage {
    HWND window{nullptr};
  };

  struct loadbuffer_storage : hooks::hook_storage {
    utils::once_flag init_flag;
  };
}

namespace hooks {
  void initialize();

  inline hooks::hook<hooks::present_storage> present;
  inline hooks::hook<> resize_buffers;
  inline hooks::hook<hooks::wndproc_storage> wndproc;
  inline hooks::hook<hooks::loadbuffer_storage> loadbuffer;
  inline hooks::hook<> error;
  inline hooks::hook<> update;
}
