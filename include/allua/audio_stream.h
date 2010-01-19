#ifndef allua_AUDIO_STREAM_H
#define allua_AUDIO_STREAM_H

#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>
#include <lua5.1/lauxlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>

typedef ALLEGRO_AUDIO_STREAM* ALLUA_audio_stream;

struct ALLUA_audio_stream_s
{
	ALLEGRO_AUDIO_STREAM* audio_stream;
	int gc_allowed;
};

/* Function: allua_register_audio_stream
 * Registers audio_stream functionality to the lua state.
 * */
int allua_register_audio_stream (lua_State* L);

/* Function: allua_check_audio_stream
 * Returns:
 * Pointer to audio_stream instance.
 * */
ALLUA_audio_stream allua_check_audio_stream (lua_State *L, int index);//, int *gc_allowed);
struct ALLUA_audio_stream_s *allua_pushaudio_stream (lua_State *L, ALLUA_audio_stream im, int gc_allowed);

#endif
