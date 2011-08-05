#ifndef allua_VOICE_H
#define allua_VOICE_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>

typedef ALLEGRO_VOICE *ALLUA_voice;

struct ALLUA_voice_s
{
   ALLEGRO_VOICE *voice;
   int gc_allowed;
};

/* Function: allua_register_voice
 * Registers voice functionality to the lua state.
 * */
int allua_register_voice(lua_State * L);

/* Function: allua_check_voice
 * Returns:
 * Pointer to voice instance.
 * */
ALLUA_voice allua_check_voice(lua_State * L, int index /* int *gc_allowed */ );
struct ALLUA_voice_s *allua_pushvoice(lua_State * L, ALLUA_voice im,
                                      int gc_allowed);

#endif
