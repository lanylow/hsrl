#include <offsets.hpp>

void offsets::initialize() {
  offsets::luaL_checklstring = offsets::get_exported("xluau", "luaL_checklstring");
  offsets::luaL_checkinteger = offsets::get_exported("xluau", "luaL_checkinteger");
  offsets::luaL_newmetatable = offsets::get_exported("xluau", "luaL_newmetatable");
  offsets::luaL_checkudata = offsets::get_exported("xluau", "luaL_checkudata");
  offsets::luaL_newstate = offsets::get_exported("xluau", "luaL_newstate");
  offsets::luaL_loadstring = offsets::get_exported("xluau", "luaL_loadstring");

  offsets::lua_settop = offsets::get_exported("xluau", "lua_settop");
  offsets::lua_pushvalue = offsets::get_exported("xluau", "lua_pushvalue");
  offsets::lua_type = offsets::get_exported("xluau", "lua_type");
  offsets::lua_tolstring = offsets::get_exported("xluau", "lua_tolstring");
  offsets::lua_pushinteger = offsets::get_exported("xluau", "lua_pushinteger");
  offsets::lua_pushcclosurek = offsets::get_exported("xluau", "lua_pushcclosurek");
  offsets::lua_pushboolean = offsets::get_exported("xluau", "lua_pushboolean");
  offsets::lua_getfield = offsets::get_exported("xluau", "lua_getfield");
  offsets::lua_createtable = offsets::get_exported("xluau", "lua_createtable");
  offsets::lua_newuserdatatagged = offsets::get_exported("xluau", "lua_newuserdatatagged");
  offsets::lua_setfield = offsets::get_exported("xluau", "lua_setfield");
  offsets::lua_setmetatable = offsets::get_exported("xluau", "lua_setmetatable");
  offsets::lua_pcall = offsets::get_exported("xluau", "lua_pcall");
  offsets::lua_error = offsets::get_exported("xluau", "lua_error");

  offsets::xluaL_loadbuffer = offsets::get_exported("xluau", "xluaL_loadbuffer");
  offsets::xlua_getglobal = offsets::get_exported("xluau", "xlua_getglobal");
  offsets::xlua_setglobal = offsets::get_exported("xluau", "xlua_setglobal");

  offsets::map_update = offsets::get_offset("GameAssembly", 0x3203050);
}