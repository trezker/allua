#include "../include/allua/mixer.h"
#include "../include/allua/sample.h"
#include "../include/allua/sample_instance.h"
#include "../include/allua/audio_stream.h"
#include "../include/allua/voice.h"
#include <stdio.h>

#define MIXER_STRING "mixer"

/* Common handlers
 * */
/*static ALLUA_mixer tomixer (lua_State *L, int index)//, int *gc_allowed)
{
  struct ALLUA_mixer_s *pi = (struct ALLUA_mixer_s*)lua_touserdata(L, index);
  if (pi == NULL) luaL_typerror(L, index, MIXER_STRING);
//  if(gc_allowed)
//  	*gc_allowed = pi->gc_allowed;
  return pi->mixer;
}
*/
ALLUA_mixer allua_check_mixer(lua_State * L, int index)
{
   struct ALLUA_mixer_s *pi;
   ALLUA_mixer im;
   luaL_checktype(L, index, LUA_TUSERDATA);
   pi = (struct ALLUA_mixer_s *)luaL_checkudata(L, index, MIXER_STRING);
   if (pi == NULL)
      luaL_typerror(L, index, MIXER_STRING);
   im = pi->mixer;
   if (!im)
      luaL_error(L, "null mixer");
   return im;
}

struct ALLUA_mixer_s *allua_pushmixer(lua_State * L, ALLUA_mixer im,
                                      int gc_allowed)
{
   struct ALLUA_mixer_s *pi;
   if (!im) {
      lua_pushnil(L);
      return NULL;
   }
   pi = (struct ALLUA_mixer_s *)lua_newuserdata(L,
                                                sizeof(struct ALLUA_mixer_s));
   pi->mixer = im;
   pi->gc_allowed = gc_allowed;
   luaL_getmetatable(L, MIXER_STRING);
   lua_setmetatable(L, -2);
   return pi;
}

/* Constructor and methods
 * */

static int allua_mixer_create(lua_State * L)
{
   int freq = luaL_checkint(L, 1);
   int depth = luaL_checkint(L, 2);
   int chan_conf = luaL_checkint(L, 3);
   ALLUA_mixer mixer = al_create_mixer(freq, depth, chan_conf);
   if (mixer)
      allua_pushmixer(L, mixer, true);
   else
      lua_pushnil(L);

   return 1;
}

static int allua_mixer_get_default(lua_State * L)
{
   ALLUA_mixer mixer = al_get_default_mixer();
   if (mixer)
      allua_pushmixer(L, mixer, false);
   else
      lua_pushnil(L);
   return 1;
}

static int allua_mixer_set_default(lua_State * L)
{
   ALLUA_mixer mixer = allua_check_mixer(L, 1);
   lua_pushboolean(L, al_set_default_mixer(mixer));
   return 1;
}

static int allua_mixer_restore_default(lua_State * L)
{
   lua_pushboolean(L, al_restore_default_mixer());
   return 1;
}

static int allua_mixer_attach_voice(lua_State * L)
{
   ALLUA_mixer mixer = allua_check_mixer(L, 1);
   ALLUA_voice voice = allua_check_voice(L, 2);
   lua_pushboolean(L, al_attach_mixer_to_voice(mixer, voice));
   return 1;
}

static int allua_mixer_attach_mixer(lua_State * L)
{
   ALLUA_mixer mixer = allua_check_mixer(L, 1);
   ALLUA_mixer stream = allua_check_mixer(L, 2);
   lua_pushboolean(L, al_attach_mixer_to_mixer(stream, mixer));
   return 1;
}

static int allua_mixer_attach_sample(lua_State * L)
{
   ALLUA_mixer mixer = allua_check_mixer(L, 1);
   ALLUA_sample_instance sample_instance = allua_check_sample_instance(L, 2);
   lua_pushboolean(L,
                   al_attach_sample_instance_to_mixer(sample_instance, mixer));
   return 1;
}

static int allua_mixer_attach_audio_stream(lua_State * L)
{
   ALLUA_mixer mixer = allua_check_mixer(L, 1);
   ALLUA_audio_stream stream = allua_check_audio_stream(L, 2);
   lua_pushboolean(L, al_attach_audio_stream_to_mixer(stream, mixer));
   return 1;
}

static int allua_mixer_get_frequency(lua_State * L)
{
   ALLUA_mixer mixer = allua_check_mixer(L, 1);
   lua_pushnumber(L, al_get_mixer_frequency(mixer));
   return 1;
}

static int allua_mixer_set_frequency(lua_State * L)
{
   ALLUA_mixer mixer = allua_check_mixer(L, 1);
   unsigned long val = luaL_checkint(L, 2);
   lua_pushboolean(L, al_set_mixer_frequency(mixer, val));
   return 1;
}

static int allua_mixer_get_channels(lua_State * L)
{
   ALLUA_mixer mixer = allua_check_mixer(L, 1);
   lua_pushnumber(L, al_get_mixer_channels(mixer));
   return 1;
}

static int allua_mixer_get_depth(lua_State * L)
{
   ALLUA_mixer mixer = allua_check_mixer(L, 1);
   lua_pushnumber(L, al_get_mixer_depth(mixer));
   return 1;
}

static int allua_mixer_get_quality(lua_State * L)
{
   ALLUA_mixer mixer = allua_check_mixer(L, 1);
   lua_pushnumber(L, al_get_mixer_quality(mixer));
   return 1;
}

static int allua_mixer_set_quality(lua_State * L)
{
   ALLUA_mixer mixer = allua_check_mixer(L, 1);
   int val = luaL_checkint(L, 2);
   lua_pushboolean(L, al_set_mixer_quality(mixer, val));
   return 1;
}

static int allua_mixer_get_playing(lua_State * L)
{
   ALLUA_mixer mixer = allua_check_mixer(L, 1);
   lua_pushboolean(L, al_get_mixer_playing(mixer));
   return 1;
}

static int allua_mixer_set_playing(lua_State * L)
{
   ALLUA_mixer mixer = allua_check_mixer(L, 1);
   bool val = lua_toboolean(L, 2);
   lua_pushboolean(L, al_set_mixer_playing(mixer, val));
   return 1;
}

static int allua_mixer_get_attached(lua_State * L)
{
   ALLUA_mixer mixer = allua_check_mixer(L, 1);
   lua_pushboolean(L, al_get_mixer_attached(mixer));
   return 1;
}

static int allua_mixer_detach(lua_State * L)
{
   ALLUA_mixer mixer = allua_check_mixer(L, 1);
   lua_pushboolean(L, al_detach_mixer(mixer));
   return 1;
}

static const luaL_reg allua_mixer_methods[] = {
   {"create", allua_mixer_create},
   {"get_default", allua_mixer_get_default},
   {"set_default", allua_mixer_set_default},
   {"restore_default", allua_mixer_restore_default},
   {"attach_voice", allua_mixer_attach_voice},
   {"attach_mixer", allua_mixer_attach_mixer},
   {"attach_sample", allua_mixer_attach_sample},
   {"attach_audio_stream", allua_mixer_attach_audio_stream},
   {"get_frequency", allua_mixer_get_frequency},
   {"set_frequency", allua_mixer_set_frequency},
   {"get_channels", allua_mixer_get_channels},
   {"get_depth", allua_mixer_get_depth},
   {"get_quality", allua_mixer_get_quality},
   {"set_quality", allua_mixer_set_quality},
   {"get_playing", allua_mixer_get_playing},
   {"set_playing", allua_mixer_set_playing},
   {"get_attached", allua_mixer_get_attached},
   {"detach", allua_mixer_detach},
   {0, 0}
};

/* GC and meta
 * */
static int allua_mixer_gc(lua_State * L)
{
   struct ALLUA_mixer_s *pi = (struct ALLUA_mixer_s *)lua_touserdata(L, 1);
   if (pi->gc_allowed) {
      ALLUA_mixer im = pi->mixer;
      printf("goodbye mixer (%p)\n", (void *)im);
      if (im)
         al_destroy_mixer(im);
   }
   return 0;
}

static int allua_mixer_tostring(lua_State * L)
{
   lua_pushfstring(L, "mixer: %p", lua_touserdata(L, 1));
   return 1;
}

static const luaL_reg allua_mixer_meta[] = {
   {"__gc", allua_mixer_gc},
   {"__tostring", allua_mixer_tostring},
   {0, 0}
};

/* Other attributes
 * */
void allua_mixer_set_attributes(lua_State * L)
{
}

/* Register
 * */
int allua_register_mixer(lua_State * L)
{
   lua_newtable(L);
   luaL_register(L, NULL, allua_mixer_methods); /* create methods table,
                                                   add it to the globals */

   allua_mixer_set_attributes(L);

   luaL_newmetatable(L, MIXER_STRING);  /* create metatable for Image,
                                           add it to the Lua registry */
   luaL_register(L, 0, allua_mixer_meta);       /* fill metatable */
   lua_pushliteral(L, "__index");
   lua_pushvalue(L, -3);        /* dup methods table */
   lua_rawset(L, -3);           /* metatable.__index = methods */
   lua_pushliteral(L, "__metatable");
   lua_pushvalue(L, -3);        /* dup methods table */
   lua_rawset(L, -3);           /* hide metatable:
                                   metatable.__metatable = methods */
   lua_pop(L, 1);               /* drop metatable */

   lua_setfield(L, -2, MIXER_STRING);

   return 0;                    /* return methods on the stack */
}
