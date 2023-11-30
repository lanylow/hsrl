#include <offsets.hpp>

void offsets::initialize() {
  offsets::luaL_checklstring = offsets::get_exported("xlua", "luaL_checklstring");
  offsets::luaL_newstate = offsets::get_exported("xlua", "luaL_newstate");
  offsets::luaL_loadstring = offsets::get_exported("xlua", "luaL_loadstring");
  offsets::luaL_setfuncs = offsets::get_exported("xlua", "luaL_setfuncs");

  offsets::lua_settop = offsets::get_exported("xlua", "lua_settop");
  offsets::lua_pushvalue = offsets::get_exported("xlua", "lua_pushvalue");
  offsets::lua_type = offsets::get_exported("xlua", "lua_type");
  offsets::lua_tolstring = offsets::get_exported("xlua", "lua_tolstring");
  offsets::lua_pushfstring = offsets::get_exported("xlua", "lua_pushfstring");
  offsets::lua_pushcclosure = offsets::get_exported("xlua", "lua_pushcclosure");
  offsets::lua_getfield = offsets::get_exported("xlua", "lua_getfield");
  offsets::lua_createtable = offsets::get_exported("xlua", "lua_createtable");
  offsets::lua_setfield = offsets::get_exported("xlua", "lua_setfield");
  offsets::lua_pcall = offsets::get_exported("xlua", "lua_pcall");
  offsets::lua_dump = offsets::get_exported("xlua", "lua_dump");
  offsets::lua_error = offsets::get_exported("xlua", "lua_error");

  offsets::xluaL_loadbuffer = offsets::get_exported("xlua", "xluaL_loadbuffer");
  offsets::xlua_getglobal = offsets::get_exported("xlua", "xlua_getglobal");
  offsets::xlua_setglobal = offsets::get_exported("xlua", "xlua_setglobal");
}