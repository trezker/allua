#ifndef allua_SAMPLE_ID_H
#define allua_SAMPLE_ID_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>

typedef ALLEGRO_SAMPLE_ID ALLUA_sample_id;

/* Function: allua_register_sample_id
 * Registers sample_id functionality to the lua state.
 * */
int allua_register_sample_id (lua_State* L);

/* Function: allua_check_sample_id
 * Returns:
 * Pointer to sample_id instance.
 * */
ALLUA_sample_id allua_check_sample_id (lua_State *L, int index);
ALLUA_sample_id *allua_pushsample_id (lua_State *L, ALLUA_sample_id im);

#endif
