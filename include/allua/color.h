#ifndef AL_LUA_COLOR_H
#define AL_LUA_COLOR_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <allegro5/allegro5.h>

typedef ALLEGRO_COLOR AL_color;

/* Function: al_lua_register_color
 * Registers Color functionality to the lua state.
 * */
int al_lua_register_color (lua_State* L);

/* Function: al_lua_check_color
 * Returns:
 * Pointer to Color instance.
 * */
AL_color al_lua_check_color (lua_State *L, int index);
AL_color *pushColor (lua_State *L, AL_color im);

#endif
