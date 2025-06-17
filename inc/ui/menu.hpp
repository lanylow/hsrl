#pragma once

#include <utils/once.hpp>
#include <textedit/TextEditor.h>

namespace ui::menu {
  void render();

  inline bool opened = false;
  inline utils::once_flag text_editor_flag;
  inline TextEditor text_editor;
}
