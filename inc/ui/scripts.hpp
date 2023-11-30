#pragma once

#include <vector>
#include <mutex>

namespace ui::scripts {
  struct window_t {
    std::string title;
  };
}

namespace ui::scripts {
  void render();

  inline std::vector<ui::scripts::window_t*> windows;
  inline std::mutex windows_mutex;
}