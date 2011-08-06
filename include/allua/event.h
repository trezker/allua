#ifndef allua_event_h
#define allua_event_h

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <allegro5/allegro5.h>

/* Function: allua_register_event
 * Registers Event functionality to the lua state.
 * */
int allua_register_event(lua_State * L);

/* Function: allua_check_event
 * Returns:
 * Event
 * */
ALLEGRO_EVENT allua_check_event(lua_State * L, int index);


ALLEGRO_EVENT *allua_pushEvent(lua_State * L, ALLEGRO_EVENT im);

/* vim: set sts=3 sw=3 et: */
#endif
