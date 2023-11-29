#include <ui/console.hpp>
#include <ui/menu.hpp>
#include <ui/ui.hpp>

void ui::console::render() {
  std::unique_lock guard{ ui::console::lines_mutex };

  if (!ui::menu::opened || !ui::console::opened)
    return;

  ImGui::Begin("HSRL Console", nullptr, ImGuiWindowFlags_AlwaysVerticalScrollbar);
  {
    ImGui::PushFont(ui::consolas);

    for (const auto& line : ui::console::lines)
      ImGui::Text(line.data());

    ImGui::PopFont();
  }
  ImGui::End();
}

void ui::console::add(std::string_view line) {
  std::unique_lock guard{ ui::console::lines_mutex };
  ui::console::lines.emplace_back(line);
}

void ui::console::clear() {
  std::unique_lock guard{ ui::console::lines_mutex };
  ui::console::lines.clear();
}