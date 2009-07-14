#ifndef allua_STREAM_H
#define allua_STREAM_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/kcm_audio.h>

typedef ALLEGRO_STREAM* ALLUA_stream;

struct ALLUA_stream_s
{
	ALLEGRO_STREAM* stream;
	int gc_allowed;
};

/* Function: allua_register_stream
 * Registers stream functionality to the lua state.
 * */
int allua_register_stream (lua_State* L);

/* Function: allua_check_stream
 * Returns:
 * Pointer to stream instance.
 * */
ALLUA_stream allua_check_stream (lua_State *L, int index);//, int *gc_allowed);
struct ALLUA_stream_s *allua_pushstream (lua_State *L, ALLUA_stream im, int gc_allowed);

#endif
