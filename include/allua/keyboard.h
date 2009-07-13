#ifndef allua_KEYBOARD_H
#define allua_KEYBOARD_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <allegro5/allegro5.h>

typedef ALLEGRO_KEYBOARD* AL_keyboard;

/* Function: allua_register_keyboard
 * Registers Keyboard functionality to the lua state.
 * */
int allua_register_keyboard (lua_State* L);

/* Function: allua_check_keyboard
 * Returns:
 * Pointer to Keyboard instance.
 * */
AL_keyboard allua_check_keyboard (lua_State *L, int index);

#endif
