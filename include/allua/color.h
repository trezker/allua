#ifndef allua_COLOR_H
#define allua_COLOR_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <allegro5/allegro5.h>

typedef ALLEGRO_COLOR AL_color;

/* Function: allua_register_color
 * Registers Color functionality to the lua state.
 * */
int allua_register_color (lua_State* L);

/* Function: allua_check_color
 * Returns:
 * Pointer to Color instance.
 * */
AL_color allua_check_color (lua_State *L, int index);
AL_color *allua_pushColor (lua_State *L, AL_color im);

#endif
