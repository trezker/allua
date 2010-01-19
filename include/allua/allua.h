#ifndef allegro5_lua_h
#define allegro5_lua_h

#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>
#include <lua5.1/lauxlib.h>

#define Set_literal(key, value, index) lua_pushliteral(L, key);\
	lua_pushinteger(L, value);\
	lua_settable (L, index);

#define Set_string(key, value, index) lua_pushstring(L, key);\
	lua_pushinteger(L, value);\
	lua_settable (L, index);

/* Function: allua_register
 * Registers all subsystem functionality to the lua state.
 * */
int allua_register(lua_State *L);

#endif
