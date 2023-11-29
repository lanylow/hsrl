#pragma once

#include <imgui/imgui.h>

#include <windows.h>

namespace ui {
  void initialize();
  void begin();
  void end();

  long long handle_message(HWND window, unsigned int message, unsigned long long wparam, long long lparam);

  inline ImFont* tahoma;
  inline ImFont* consolas;
}