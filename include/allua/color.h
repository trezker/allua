#ifndef allua_COLOR_H
#define allua_COLOR_H

#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>
#include <lua5.1/lauxlib.h>
#include <allegro5/allegro5.h>

typedef ALLEGRO_COLOR ALLUA_color;

/* Function: allua_register_color
 * Registers Color functionality to the lua state.
 * */
int allua_register_color (lua_State* L);

/* Function: allua_check_color
 * Returns:
 * Pointer to Color instance.
 * */
ALLUA_color allua_check_color (lua_State *L, int index);
ALLUA_color *allua_pushColor (lua_State *L, ALLUA_color im);

#endif
