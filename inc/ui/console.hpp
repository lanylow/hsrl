#pragma once

#include <vector>
#include <mutex>

namespace ui::console {
  void render();

  void add(std::string_view line);
  void clear();

  inline bool opened = false;
  inline std::vector<std::string_view> lines;
  inline std::mutex lines_mutex;
}