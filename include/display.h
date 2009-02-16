#ifndef AL_LUA_DISPLAY_H
#define AL_LUA_DISPLAY_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <allegro5/allegro5.h>

typedef ALLEGRO_DISPLAY* AL_Display;

/* Function: al_lua_register_display
 * Registers Display functionality to the lua state.
 * */
int al_lua_register_display (lua_State* L);

/* Function: al_lua_check_display
 * Returns:
 * Pointer to Display instance.
 * */
AL_Display al_lua_check_display (lua_State *L, int index);

#endif
