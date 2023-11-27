#include <menu.hpp>
#include <hooks/hooks.hpp>
#include <runtime.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_dx11.h>
#include <imgui/imgui_impl_win32.h>
#include <textedit/TextEditor.h>

#include <format>

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void menu::initialize() {
  ImGui::CreateContext();

  auto io = ImGui::GetIO();
  io.IniFilename = nullptr;
  io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
  io.Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\tahoma.ttf)", 14.f);
  editor_font = io.Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\consola.ttf)", 16.f);

  ImGui_ImplWin32_Init(hooks::wndproc.storage.window);
  ImGui_ImplDX11_Init(hooks::present.storage.device, hooks::present.storage.context);
}

void menu::begin() {
  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();
  ImGui::NewFrame();
}

void menu::end() {
  ImGui::EndFrame();
  ImGui::Render();

  hooks::present.storage.context->OMSetRenderTargets(1, &hooks::present.storage.render_target, nullptr);
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

long long menu::handle_message(HWND window, unsigned int message, unsigned long long wparam, long long lparam) {
  if (message == WM_KEYDOWN && wparam == VK_INSERT)
    menu::opened = !menu::opened;

  return ImGui_ImplWin32_WndProcHandler(window, message, wparam, lparam);
}

void menu::render_menu() {
  if (!menu::opened)
    return;

  utils::call_once(menu::text_editor_flag, [] {
    menu::text_editor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());
    menu::text_editor.SetPalette(TextEditor::GetDarkPalette());
    menu::text_editor.SetTabSize(2);
    menu::text_editor.SetShowWhitespaces(false);
    menu::text_editor.SetColorizerEnable(true);
  });

  ImGui::Begin("HSRL - Honkai: Star Rail Lua", nullptr, ImGuiWindowFlags_HorizontalScrollbar);
  {
    ImGui::SetWindowSize({ 800, 600 }, ImGuiCond_Once);

    if (ImGui::Button("Run")) {
      const auto code = menu::text_editor.GetText();

      if (!code.empty() && code.find_first_not_of(" \t\n\v\f\r") != std::string::npos) {
        const auto compiled = runtime::compile(code);

        if (compiled.has_value())
          runtime::do_buffer(compiled.value());
      }
    }

    ImGui::PushFont(editor_font);
    menu::text_editor.Render("LuaEditor");
    ImGui::PopFont();
  }
  ImGui::End();
}