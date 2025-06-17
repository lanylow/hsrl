#include <windows.h>

#include <thread>
#include <chrono>
#include <print>

#include <utils/console.hpp>
#include <hooks/hooks.hpp>
#include <offsets.hpp>

using namespace std::chrono_literals;

void initialize() {
  utils::console::attach("HSRL - Honkai: Star Rail Lua");
  std::println("Waiting for GameAssembly.dll and xluau.dll");

  while (!GetModuleHandleA("GameAssembly.dll") || !GetModuleHandleA("xluau.dll"))
    std::this_thread::sleep_for(10ms);

  offsets::initialize();
  hooks::initialize();
}

bool DllMain(const HMODULE module, const unsigned int reason, [[maybe_unused]] void* reserved) {
  DisableThreadLibraryCalls(module);

  if (reason == DLL_PROCESS_ATTACH)
    if (const auto handle = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)(initialize), nullptr, 0, nullptr))
      CloseHandle(handle);

  return true;
}
