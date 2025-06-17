#include <ui/ui.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_dx11.h>
#include <imgui/imgui_impl_win32.h>

#include <ui/menu.hpp>
#include <hooks/hooks.hpp>

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void ui::initialize() {
  ImGui::CreateContext();

  auto io = ImGui::GetIO();
  io.IniFilename = nullptr;
  io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

  ui::tahoma = io.Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\tahoma.ttf)", 14.f);
  ui::consolas = io.Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\consola.ttf)", 14.f);

  ImGui_ImplWin32_Init(hooks::wndproc.get_storage().window);
  ImGui_ImplDX11_Init(hooks::present.get_storage().device, hooks::present.get_storage().context);
}

void ui::begin() {
  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();
  ImGui::NewFrame();
  ImGui::PushFont(ui::tahoma);
}

void ui::end() {
  ImGui::PopFont();
  ImGui::EndFrame();
  ImGui::Render();

  hooks::present.get_storage().context->OMSetRenderTargets(1, &hooks::present.get_storage().render_target, nullptr);
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

long long ui::handle_message(HWND window, unsigned int message, unsigned long long wparam, long long lparam) {
  if (message == WM_KEYDOWN && wparam == VK_INSERT)
    ui::menu::opened = !ui::menu::opened;

  return ImGui_ImplWin32_WndProcHandler(window, message, wparam, lparam);
}