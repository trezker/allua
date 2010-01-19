#ifndef allua_event_h
#define allua_event_h

#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>
#include <lua5.1/lauxlib.h>
#include <allegro5/allegro5.h>

/* Function: allua_register_event
 * Registers Event functionality to the lua state.
 * */
int allua_register_event (lua_State* L);

/* Function: allua_check_event
 * Returns:
 * Event
 * */
ALLEGRO_EVENT allua_check_event (lua_State *L, int index);


ALLEGRO_EVENT *allua_pushEvent (lua_State *L, ALLEGRO_EVENT im);

#endif
