#ifndef allua_MOUSE_H
#define allua_MOUSE_H

#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>
#include <lua5.1/lauxlib.h>
#include <allegro5/allegro5.h>

typedef ALLEGRO_MOUSE* ALLUA_mouse;

/* Function: allua_register_mouse
 * Registers Mouse functionality to the lua state.
 * */
int allua_register_mouse (lua_State* L);

/* Function: allua_check_mouse
 * Returns:
 * Pointer to Mouse instance.
 * */
ALLUA_mouse allua_check_mouse (lua_State *L, int index);

#endif
