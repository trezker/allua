#include "../include/allua/audio_stream.h"
#include <stdio.h>

#define AUDIO_STREAM_STRING "audio_stream"

/* Common handlers
 * */
/*static ALLUA_audio_stream toaudio_stream (lua_State *L, int index)//, int *gc_allowed)
{
  struct ALLUA_audio_stream_s *pi = (struct ALLUA_audio_stream_s*)lua_touserdata(L, index);
  if (pi == NULL) luaL_typerror(L, index, AUDIO_STREAM_STRING);
//  if(gc_allowed)
//  	*gc_allowed = pi->gc_allowed;
  return pi->audio_stream;
}
*/
ALLUA_audio_stream allua_check_audio_stream(lua_State * L,
                                            int index /* int *gc_allowed */ )
{
   struct ALLUA_audio_stream_s *pi;
   ALLUA_audio_stream im;
   luaL_checktype(L, index, LUA_TUSERDATA);
   pi = (struct ALLUA_audio_stream_s *)luaL_checkudata(L, index,
                                                       AUDIO_STREAM_STRING);
   if (pi == NULL)
      luaL_typerror(L, index, AUDIO_STREAM_STRING);
   im = pi->audio_stream;
   if (!im)
      luaL_error(L, "null audio_stream");
   return im;
}

struct ALLUA_audio_stream_s *allua_pushaudio_stream(lua_State * L,
                                                    ALLUA_audio_stream im,
                                                    int gc_allowed)
{
   struct ALLUA_audio_stream_s *pi =
       (struct ALLUA_audio_stream_s *)lua_newuserdata(L,
                                                      sizeof(struct
                                                             ALLUA_audio_stream_s));
   pi->audio_stream = im;
   pi->gc_allowed = gc_allowed;
   luaL_getmetatable(L, AUDIO_STREAM_STRING);
   lua_setmetatable(L, -2);
   return pi;
}

/* Constructor and methods
 * */

static int allua_audio_stream_create(lua_State * L)
{
   int buffer_count = luaL_checkint(L, 1);
   int samples = luaL_checkint(L, 2);
   int freq = luaL_checkint(L, 3);
   int depth = luaL_checkint(L, 4);
   int chan_conf = luaL_checkint(L, 5);

   ALLEGRO_AUDIO_STREAM *stream =
       al_create_audio_stream(buffer_count, samples, freq, depth, chan_conf);
   if (stream)
      allua_pushaudio_stream(L, stream, true);
   else
      lua_pushnil(L);
   return 1;
}

static int allua_audio_stream_load(lua_State * L)
{
   const char *filename = luaL_checkstring(L, 1);
   int buffer_count = luaL_checkint(L, 2);
   int samples = luaL_checkint(L, 3);

   ALLEGRO_AUDIO_STREAM *stream =
       al_load_audio_stream(filename, buffer_count, samples);
   if (stream)
      allua_pushaudio_stream(L, stream, true);
   else
      lua_pushnil(L);

   return 1;
}

static int allua_audio_stream_rewind(lua_State * L)
{
   ALLUA_audio_stream audio_stream = allua_check_audio_stream(L, 1);
   lua_pushboolean(L, al_rewind_audio_stream(audio_stream));
   return 1;
}

static int allua_audio_stream_get_frequency(lua_State * L)
{
   ALLUA_audio_stream audio_stream = allua_check_audio_stream(L, 1);
   lua_pushnumber(L, al_get_audio_stream_frequency(audio_stream));
   return 1;
}

static int allua_audio_stream_get_channels(lua_State * L)
{
   ALLUA_audio_stream audio_stream = allua_check_audio_stream(L, 1);
   lua_pushnumber(L, al_get_audio_stream_channels(audio_stream));
   return 1;
}

static int allua_audio_stream_get_depth(lua_State * L)
{
   ALLUA_audio_stream audio_stream = allua_check_audio_stream(L, 1);
   lua_pushnumber(L, al_get_audio_stream_depth(audio_stream));
   return 1;
}

static int allua_audio_stream_get_length(lua_State * L)
{
   ALLUA_audio_stream audio_stream = allua_check_audio_stream(L, 1);
   lua_pushnumber(L, al_get_audio_stream_length(audio_stream));
   return 1;
}

static int allua_audio_stream_get_speed(lua_State * L)
{
   ALLUA_audio_stream audio_stream = allua_check_audio_stream(L, 1);
   lua_pushnumber(L, al_get_audio_stream_speed(audio_stream));
   return 1;
}

static int allua_audio_stream_set_speed(lua_State * L)
{
   ALLUA_audio_stream audio_stream = allua_check_audio_stream(L, 1);
   float val = luaL_checknumber(L, 2);
   lua_pushboolean(L, al_set_audio_stream_speed(audio_stream, val));
   return 1;
}

static int allua_audio_stream_get_gain(lua_State * L)
{
   ALLUA_audio_stream audio_stream = allua_check_audio_stream(L, 1);
   lua_pushnumber(L, al_get_audio_stream_gain(audio_stream));
   return 1;
}

static int allua_audio_stream_set_gain(lua_State * L)
{
   ALLUA_audio_stream audio_stream = allua_check_audio_stream(L, 1);
   float val = luaL_checknumber(L, 2);
   lua_pushboolean(L, al_set_audio_stream_gain(audio_stream, val));
   return 1;
}

static int allua_audio_stream_get_pan(lua_State * L)
{
   ALLUA_audio_stream audio_stream = allua_check_audio_stream(L, 1);
   lua_pushnumber(L, al_get_audio_stream_pan(audio_stream));
   return 1;
}

static int allua_audio_stream_set_pan(lua_State * L)
{
   ALLUA_audio_stream audio_stream = allua_check_audio_stream(L, 1);
   float val = luaL_checknumber(L, 2);
   lua_pushboolean(L, al_set_audio_stream_pan(audio_stream, val));
   return 1;
}

static int allua_audio_stream_get_playing(lua_State * L)
{
   ALLUA_audio_stream audio_stream = allua_check_audio_stream(L, 1);
   lua_pushboolean(L, al_get_audio_stream_playing(audio_stream));
   return 1;
}

static int allua_audio_stream_set_playing(lua_State * L)
{
   ALLUA_audio_stream audio_stream = allua_check_audio_stream(L, 1);
   float val = lua_toboolean(L, 2);
   lua_pushboolean(L, al_set_audio_stream_playing(audio_stream, val));
   return 1;
}

static int allua_audio_stream_get_playmode(lua_State * L)
{
   ALLUA_audio_stream audio_stream = allua_check_audio_stream(L, 1);
   lua_pushnumber(L, al_get_audio_stream_playmode(audio_stream));
   return 1;
}

static int allua_audio_stream_set_playmode(lua_State * L)
{
   ALLUA_audio_stream audio_stream = allua_check_audio_stream(L, 1);
   int val = luaL_checkint(L, 2);
   lua_pushboolean(L, al_set_audio_stream_playmode(audio_stream, val));
   return 1;
}

static int allua_audio_stream_get_attached(lua_State * L)
{
   ALLUA_audio_stream audio_stream = allua_check_audio_stream(L, 1);
   lua_pushboolean(L, al_get_audio_stream_attached(audio_stream));
   return 1;
}

static int allua_audio_stream_detach(lua_State * L)
{
   ALLUA_audio_stream audio_stream = allua_check_audio_stream(L, 1);
   lua_pushboolean(L, al_detach_audio_stream(audio_stream));
   return 1;
}

static int allua_audio_stream_seek_secs(lua_State * L)
{
   ALLUA_audio_stream audio_stream = allua_check_audio_stream(L, 1);
   double t = luaL_checknumber(L, 2);
   lua_pushboolean(L, al_seek_audio_stream_secs(audio_stream, t));
   return 1;
}

static int allua_audio_stream_get_position_secs(lua_State * L)
{
   ALLUA_audio_stream audio_stream = allua_check_audio_stream(L, 1);
   lua_pushnumber(L, al_get_audio_stream_position_secs(audio_stream));
   return 1;
}

static int allua_audio_stream_get_length_secs(lua_State * L)
{
   ALLUA_audio_stream audio_stream = allua_check_audio_stream(L, 1);
   lua_pushnumber(L, al_get_audio_stream_length_secs(audio_stream));
   return 1;
}

static int allua_audio_stream_set_loop_secs(lua_State * L)
{
   ALLUA_audio_stream audio_stream = allua_check_audio_stream(L, 1);
   double start = luaL_checknumber(L, 2);
   double end = luaL_checknumber(L, 3);
   lua_pushboolean(L, al_set_audio_stream_loop_secs(audio_stream, start, end));
   return 1;
}

static const luaL_reg allua_audio_stream_methods[] = {
   {"create", allua_audio_stream_create},
   {"load", allua_audio_stream_load},
   {"rewind", allua_audio_stream_rewind},
   {"get_frequency", allua_audio_stream_get_frequency},
   {"get_channels", allua_audio_stream_get_channels},
   {"get_depth", allua_audio_stream_get_depth},
   {"get_length", allua_audio_stream_get_length},
   {"get_speed", allua_audio_stream_get_speed},
   {"set_speed", allua_audio_stream_set_speed},
   {"get_gain", allua_audio_stream_get_gain},
   {"set_gain", allua_audio_stream_set_gain},
   {"get_pan", allua_audio_stream_get_pan},
   {"set_pan", allua_audio_stream_set_pan},
   {"get_playing", allua_audio_stream_get_playing},
   {"set_playing", allua_audio_stream_set_playing},
   {"get_playmode", allua_audio_stream_get_playmode},
   {"set_playmode", allua_audio_stream_set_playmode},
   {"get_attached", allua_audio_stream_get_attached},
   {"detach", allua_audio_stream_detach},
   {"seek_secs", allua_audio_stream_seek_secs},
   {"get_position_secs", allua_audio_stream_get_position_secs},
   {"get_length_secs", allua_audio_stream_get_length_secs},
   {"set_loop_secs", allua_audio_stream_set_loop_secs},
   {0, 0}
};

/* GC and meta
 * */
static int allua_audio_stream_gc(lua_State * L)
{
   struct ALLUA_audio_stream_s *pi =
       (struct ALLUA_audio_stream_s *)lua_touserdata(L, 1);
   if (pi->gc_allowed) {
      ALLUA_audio_stream im = pi->audio_stream;
      printf("goodbye audio_stream (%p)\n", (void *)im);
      if (im)
         al_destroy_audio_stream(im);
   }
   return 0;
}

static int allua_audio_stream_tostring(lua_State * L)
{
   lua_pushfstring(L, "audio_stream: %p", lua_touserdata(L, 1));
   return 1;
}

static const luaL_reg allua_audio_stream_meta[] = {
   {"__gc", allua_audio_stream_gc},
   {"__tostring", allua_audio_stream_tostring},
   {0, 0}
};

/* Other attributes
 * */
void allua_audio_stream_set_attributes(lua_State * L)
{
}

/* Register
 * */
int allua_register_audio_stream(lua_State * L)
{
   lua_newtable(L);
   luaL_register(L, NULL, allua_audio_stream_methods);  /* create methods table,
                                                           add it to the globals */

   allua_audio_stream_set_attributes(L);

   luaL_newmetatable(L, AUDIO_STREAM_STRING);   /* create metatable for Image,
                                                   add it to the Lua registry */
   luaL_register(L, 0, allua_audio_stream_meta);        /* fill metatable */
   lua_pushliteral(L, "__index");
   lua_pushvalue(L, -3);        /* dup methods table */
   lua_rawset(L, -3);           /* metatable.__index = methods */
   lua_pushliteral(L, "__metatable");
   lua_pushvalue(L, -3);        /* dup methods table */
   lua_rawset(L, -3);           /* hide metatable:
                                   metatable.__metatable = methods */
   lua_pop(L, 1);               /* drop metatable */

   lua_setfield(L, -2, AUDIO_STREAM_STRING);

   return 0;                    /* return methods on the stack */
}
