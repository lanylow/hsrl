#include <ui/console.hpp>
#include <ui/menu.hpp>
#include <ui/ui.hpp>

void ui::console::render() {
  if (!ui::menu::opened || !ui::console::opened)
    return;

  ImGui::Begin("HSRL Console", nullptr, ImGuiWindowFlags_AlwaysVerticalScrollbar);
  {
    ImGui::PushFont(ui::consolas);
    std::unique_lock guard{ ui::console::lines_mutex };

    for (const auto& line : ui::console::lines)
      ImGui::Text(line.data());

    ImGui::PopFont();
  }
  ImGui::End();
}
