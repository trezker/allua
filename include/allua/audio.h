#ifndef allua_audio_H
#define allua_audio_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <allegro5/allegro5.h>

/* Function: allua_register_audio
 * Registers audio functionality to the lua state.
 * */
int allua_register_audio (lua_State* L);

#endif
