#include <hooks/hooks.hpp>
#include <hooks/endpoints.hpp>
#include <offsets.hpp>

void hooks::initialize() {
  MH_Initialize();

  hooks::loadbuffer.install(offsets::xluaL_loadbuffer, &hooks::endpoints::loadbuffer);
  hooks::error.install(offsets::lua_error, &hooks::endpoints::error);
}
