#ifndef AL_LUA_PRIMITIVES_H
#define AL_LUA_PRIMITIVES_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <allegro5/allegro5.h>

/* Function: al_lua_register_primitives
 * Registers Primitives functionality to the lua state.
 * */
int al_lua_register_primitives (lua_State* L);

#endif
