#pragma once

#include <vector>
#include <mutex>

namespace ui::scripts {
  struct window_object_t;
  struct window_t;

  enum class flag_type : uint8_t {
    boolean,
    integer
  };

  struct flag_t {
    uint32_t hash;
    ui::scripts::flag_type type;
    ui::scripts::window_object_t* object;

    union {
      bool b;
      int i;
    };
  };

  enum class window_object_type : uint8_t {
    button,
    checkbox,
    slider_int
  };

  struct window_object_t {
    virtual ~window_object_t() = default;

    ui::scripts::window_object_type type;
  };

  struct clickable_t final : ui::scripts::window_object_t {
    static ui::scripts::clickable_t* create(ui::scripts::window_t* window, const char* text, const char* flag_name, ui::scripts::window_object_type type);

    std::string text;
    ui::scripts::flag_t* flag;
  };

  struct slider_t final : ui::scripts::window_object_t {
    std::string text;
    int min, max;
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
