#ifndef allua_PRIMITIVES_H
#define allua_PRIMITIVES_H

#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>
#include <lua5.1/lauxlib.h>
#include <allegro5/allegro5.h>

/* Function: allua_register_primitives
 * Registers Primitives functionality to the lua state.
 * */
int allua_register_primitives (lua_State* L);

#endif
