#pragma once

#define DECLARE_METHOD(ret, name, arg_types, args) ret name arg_types { return ((ret(*)arg_types)(offsets::name))args; }

struct lua_State { };