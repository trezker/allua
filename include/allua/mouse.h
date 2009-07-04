#ifndef AL_LUA_MOUSE_H
#define AL_LUA_MOUSE_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <allegro5/allegro5.h>

typedef ALLEGRO_MOUSE* AL_mouse;

/* Function: al_lua_register_mouse
 * Registers Mouse functionality to the lua state.
 * */
int al_lua_register_mouse (lua_State* L);

/* Function: al_lua_check_mouse
 * Returns:
 * Pointer to Mouse instance.
 * */
AL_mouse al_lua_check_mouse (lua_State *L, int index);

#endif
