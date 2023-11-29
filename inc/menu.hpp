#pragma once

#include <utils/once.hpp>
#include <textedit/TextEditor.h>

#include <windows.h>
#include <mutex>

namespace menu {
  void initialize();
  void begin();
  void end();

  long long handle_message(HWND window, unsigned int message, unsigned long long wparam, long long lparam);
  void render_menu();

  inline bool opened = false;
  inline bool console = false;

  inline utils::once_flag text_editor_flag;
  inline TextEditor text_editor;
  inline ImFont* editor_font;

  inline std::vector<std::string_view> lines;
  inline std::mutex lines_mutex;
}