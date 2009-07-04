#ifndef AL_LUA_KEYBOARD_H
#define AL_LUA_KEYBOARD_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <allegro5/allegro5.h>

typedef ALLEGRO_KEYBOARD* AL_keyboard;

/* Function: al_lua_register_keyboard
 * Registers Keyboard functionality to the lua state.
 * */
int al_lua_register_keyboard (lua_State* L);

/* Function: al_lua_check_keyboard
 * Returns:
 * Pointer to Keyboard instance.
 * */
AL_keyboard al_lua_check_keyboard (lua_State *L, int index);

#endif
