#pragma once

#include <vector>
#include <string>
#include <mutex>

namespace ui::console {
  void render();

  inline bool opened = false;
  inline std::vector<std::string_view> lines;
  inline std::mutex lines_mutex;
}