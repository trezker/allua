#ifndef allua_SAMPLE_H
#define allua_SAMPLE_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>

typedef ALLEGRO_SAMPLE *ALLUA_sample;

struct ALLUA_sample_s
{
   ALLEGRO_SAMPLE *sample;
   int gc_allowed;
};

/* Function: allua_register_sample
 * Registers sample functionality to the lua state.
 * */
int allua_register_sample(lua_State * L);

/* Function: allua_check_sample
 * Returns:
 * Pointer to sample instance.
 * */
ALLUA_sample allua_check_sample(lua_State * L,
                                int index /* int *gc_allowed */ );
struct ALLUA_sample_s *allua_pushsample(lua_State * L, ALLUA_sample im,
                                        int gc_allowed);

#endif
