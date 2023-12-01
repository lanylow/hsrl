#pragma once

#include <vector>
#include <mutex>

namespace ui::scripts {
  struct window_object_t;

  enum class flag_type : int {
    boolean
  };

  struct flag_t {
    uint32_t hash;
    ui::scripts::flag_type type;
    ui::scripts::window_object_t* object;

    union {
      bool b;
    };
  };

  enum class window_object_type : int {
    button
  };

  struct window_object_t {
    virtual ~window_object_t() = default;

    ui::scripts::window_object_type type;
  };

  struct button_t final : window_object_t {
    std::string text;
    ui::scripts::flag_t* flag;
  };

  struct window_t {
    std::string title;
    std::vector<ui::scripts::window_object_t*> objects;
  };
}

namespace ui::scripts {
  void render();

  inline std::vector<ui::scripts::window_t*> windows;
  inline std::vector<ui::scripts::flag_t*> flags;
  inline std::mutex windows_mutex;
}