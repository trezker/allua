#ifndef allua_MOUSE_H
#define allua_MOUSE_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <allegro5/allegro5.h>

typedef ALLEGRO_MOUSE *ALLUA_mouse;

/* Function: allua_register_mouse
 * Registers Mouse functionality to the lua state.
 * */
int allua_register_mouse(lua_State * L);

/* Function: allua_check_mouse
 * Returns:
 * Pointer to Mouse instance.
 * */
ALLUA_mouse allua_check_mouse(lua_State * L, int index);

/* vim: set sts=3 sw=3 et: */
#endif
