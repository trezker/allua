#ifndef allua_filesystem_h
#define allua_filesystem_h

#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>
#include <lua5.1/lauxlib.h>
#include <allegro5/allegro5.h>

/* Function: allua_register_primitives
 * Registers filesystem functionality to the lua state.
 * */
int allua_register_filesystem (lua_State* L);

#endif
