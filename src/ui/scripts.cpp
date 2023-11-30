#include <ui/scripts.hpp>
#include <ui/menu.hpp>

void ui::scripts::render() {
  if (!ui::menu::opened)
    return;

  std::unique_lock guard{ ui::scripts::windows_mutex };

  for (const auto window : ui::scripts::windows) {
    ImGui::Begin(window->title.c_str());
    {

    }
    ImGui::End();
  }
}
