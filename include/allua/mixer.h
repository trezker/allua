#ifndef allua_MIXER_H
#define allua_MIXER_H

#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>
#include <lua5.1/lauxlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>

typedef ALLEGRO_MIXER* ALLUA_mixer;

struct ALLUA_mixer_s
{
	ALLEGRO_MIXER* mixer;
	int gc_allowed;
};

/* Function: allua_register_mixer
 * Registers mixer functionality to the lua state.
 * */
int allua_register_mixer (lua_State* L);

/* Function: allua_check_mixer
 * Returns:
 * Pointer to mixer instance.
 * */
ALLUA_mixer allua_check_mixer (lua_State *L, int index);//, int *gc_allowed);
struct ALLUA_mixer_s *allua_pushmixer (lua_State *L, ALLUA_mixer im, int gc_allowed);

#endif
