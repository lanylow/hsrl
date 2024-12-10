#include <ui/menu.hpp>
#include <ui/console.hpp>
#include <ui/ui.hpp>
#include <hooks/hooks.hpp>
#include <runtime.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_dx11.h>
#include <imgui/imgui_impl_win32.h>
#include <textedit/TextEditor.h>

#include <format>

void ui::menu::render() {
  if (!ui::menu::opened)
    return;

  utils::call_once(ui::menu::text_editor_flag, [] {
    ui::menu::text_editor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());
    ui::menu::text_editor.SetPalette(TextEditor::GetDarkPalette());
    ui::menu::text_editor.SetTabSize(2);
    ui::menu::text_editor.SetShowWhitespaces(false);
    ui::menu::text_editor.SetColorizerEnable(true);
  });

  ImGui::Begin("HSRL - Honkai: Star Rail Lua", nullptr, ImGuiWindowFlags_HorizontalScrollbar);
  {
    ImGui::SetWindowSize({ 800, 600 }, ImGuiCond_Once);

    if (ImGui::Button("Run")) {
      const auto code = ui::menu::text_editor.GetText();

      if (!code.empty() && code.find_first_not_of(" \t\n\v\f\r") != std::string::npos) {
        runtime::do_buffer(code);
      }
    }

    ImGui::SameLine();
    ImGui::Checkbox("Console", &ui::console::opened);
    ImGui::Separator();

    ImGui::PushFont(ui::consolas);
    ui::menu::text_editor.Render("LuaEditor");
    ImGui::PopFont();
  }
  ImGui::End();
}
