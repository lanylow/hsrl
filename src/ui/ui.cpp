#include <ui/ui.hpp>
#include <ui/menu.hpp>
#include <hooks/hooks.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_dx11.h>
#include <imgui/imgui_impl_win32.h>

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void ui::initialize() {
  ImGui::CreateContext();

  auto io = ImGui::GetIO();
  io.IniFilename = nullptr;
  io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

  ui::tahoma = io.Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\tahoma.ttf)", 14.f);
  ui::consolas = io.Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\consola.ttf)", 14.f);

  ImGui_ImplWin32_Init(hooks::wndproc.storage.window);
  ImGui_ImplDX11_Init(hooks::present.storage.device, hooks::present.storage.context);
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

  hooks::present.storage.context->OMSetRenderTargets(1, &hooks::present.storage.render_target, nullptr);
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

long long ui::handle_message(HWND window, unsigned int message, unsigned long long wparam, long long lparam) {
  if (message == WM_KEYDOWN && wparam == VK_INSERT)
    ui::menu::opened = !ui::menu::opened;

  return ImGui_ImplWin32_WndProcHandler(window, message, wparam, lparam);
}