#include "allua/stream.h"
#include <stdio.h>

#define STREAM_STRING "stream"

/* Common handlers
 * */
/*static ALLUA_stream tostream (lua_State *L, int index)//, int *gc_allowed)
{
  struct ALLUA_stream_s *pi = (struct ALLUA_stream_s*)lua_touserdata(L, index);
  if (pi == NULL) luaL_typerror(L, index, STREAM_STRING);
//  if(gc_allowed)
//  	*gc_allowed = pi->gc_allowed;
  return pi->stream;
}
*/
ALLUA_stream allua_check_stream (lua_State *L, int index)//, int *gc_allowed)
{
  struct ALLUA_stream_s *pi;
  ALLUA_stream im;
  luaL_checktype(L, index, LUA_TUSERDATA);
  pi = (struct ALLUA_stream_s*)luaL_checkudata(L, index, STREAM_STRING);
  if (pi == NULL)
  	luaL_typerror(L, index, STREAM_STRING);
  im = pi->stream;
  if (!im)
    luaL_error(L, "null stream");
  return im;
}

struct ALLUA_stream_s *allua_pushstream (lua_State *L, ALLUA_stream im, int gc_allowed)
{
  struct ALLUA_stream_s *pi = (struct ALLUA_stream_s *)lua_newuserdata(L, sizeof(struct ALLUA_stream_s));
  pi->stream = im;
  pi->gc_allowed = gc_allowed;
  luaL_getmetatable(L, STREAM_STRING);
  lua_setmetatable(L, -2);
  return pi;
}

/* Constructor and methods
 * */

static int allua_stream_create (lua_State *L)
{
  int buffer_count = luaL_checkint(L, 1);
  int samples = luaL_checkint(L, 2);
  int freq = luaL_checkint(L, 3);
  int depth = luaL_checkint(L, 4);
  int chan_conf = luaL_checkint(L, 5);

  allua_pushstream(L, al_create_stream(buffer_count, samples, freq, depth, chan_conf), true);

  return 1;
}

static int allua_stream_from_file (lua_State *L)
{
  const char* filename = luaL_checkstring(L, 1);
  int buffer_count = luaL_checkint(L, 2);
  int samples = luaL_checkint(L, 3);

  allua_pushstream(L, al_stream_from_file(filename, buffer_count, samples), true);

  return 1;
}

static int allua_stream_rewind (lua_State *L)
{
  ALLUA_stream stream = allua_check_stream(L, 1);
  lua_pushboolean(L, al_rewind_stream(stream));
  return 1;
}

static int allua_stream_get_frequency (lua_State *L)
{
  ALLUA_stream stream = allua_check_stream(L, 1);
  lua_pushnumber(L, al_get_stream_frequency(stream));
  return 1;
}

static int allua_stream_get_channels (lua_State *L)
{
  ALLUA_stream stream = allua_check_stream(L, 1);
  lua_pushnumber(L, al_get_stream_channels(stream));
  return 1;
}

static int allua_stream_get_depth (lua_State *L)
{
  ALLUA_stream stream = allua_check_stream(L, 1);
  lua_pushnumber(L, al_get_stream_depth(stream));
  return 1;
}

static int allua_stream_get_length (lua_State *L)
{
  ALLUA_stream stream = allua_check_stream(L, 1);
  lua_pushnumber(L, al_get_stream_length(stream));
  return 1;
}

static int allua_stream_get_speed (lua_State *L)
{
  ALLUA_stream stream = allua_check_stream(L, 1);
  lua_pushnumber(L, al_get_stream_speed(stream));
  return 1;
}

static int allua_stream_set_speed (lua_State *L)
{
  ALLUA_stream stream = allua_check_stream(L, 1);
  float val = luaL_checknumber(L, 2);
  lua_pushboolean(L, al_set_stream_speed(stream, val));
  return 1;
}

static int allua_stream_get_gain (lua_State *L)
{
  ALLUA_stream stream = allua_check_stream(L, 1);
  lua_pushnumber(L, al_get_stream_gain(stream));
  return 1;
}

static int allua_stream_set_gain (lua_State *L)
{
  ALLUA_stream stream = allua_check_stream(L, 1);
  float val = luaL_checknumber(L, 2);
  lua_pushboolean(L, al_set_stream_gain(stream, val));
  return 1;
}

static int allua_stream_get_pan (lua_State *L)
{
  ALLUA_stream stream = allua_check_stream(L, 1);
  lua_pushnumber(L, al_get_stream_pan(stream));
  return 1;
}

static int allua_stream_set_pan (lua_State *L)
{
  ALLUA_stream stream = allua_check_stream(L, 1);
  float val = luaL_checknumber(L, 2);
  lua_pushboolean(L, al_set_stream_pan(stream, val));
  return 1;
}

static int allua_stream_get_playing (lua_State *L)
{
  ALLUA_stream stream = allua_check_stream(L, 1);
  lua_pushboolean(L, al_get_stream_playing(stream));
  return 1;
}

static int allua_stream_set_playing (lua_State *L)
{
  ALLUA_stream stream = allua_check_stream(L, 1);
  float val = lua_toboolean(L, 2);
  lua_pushboolean(L, al_set_stream_playing(stream, val));
  return 1;
}

static int allua_stream_get_playmode (lua_State *L)
{
  ALLUA_stream stream = allua_check_stream(L, 1);
  lua_pushnumber(L, al_get_stream_playmode(stream));
  return 1;
}

static int allua_stream_set_playmode (lua_State *L)
{
  ALLUA_stream stream = allua_check_stream(L, 1);
  int val = luaL_checkint(L, 2);
  lua_pushboolean(L, al_set_stream_playmode(stream, val));
  return 1;
}

static int allua_stream_get_attached (lua_State *L)
{
  ALLUA_stream stream = allua_check_stream(L, 1);
  lua_pushboolean(L, al_get_stream_attached(stream));
  return 1;
}

static int allua_stream_detach (lua_State *L)
{
  ALLUA_stream stream = allua_check_stream(L, 1);
  lua_pushboolean(L, al_detach_stream(stream));
  return 1;
}

static int allua_stream_seek_secs (lua_State *L)
{
  ALLUA_stream stream = allua_check_stream(L, 1);
  double t = luaL_checknumber(L, 2);
  lua_pushboolean(L, al_seek_stream_secs(stream, t));
  return 1;
}

static int allua_stream_get_position_secs (lua_State *L)
{
  ALLUA_stream stream = allua_check_stream(L, 1);
  lua_pushnumber(L, al_get_stream_position_secs(stream));
  return 1;
}

static int allua_stream_get_length_secs (lua_State *L)
{
  ALLUA_stream stream = allua_check_stream(L, 1);
  lua_pushnumber(L, al_get_stream_length_secs(stream));
  return 1;
}

static int allua_stream_set_loop_secs (lua_State *L)
{
  ALLUA_stream stream = allua_check_stream(L, 1);
  double start = luaL_checknumber(L, 2);
  double end = luaL_checknumber(L, 3);
  lua_pushboolean(L, al_set_stream_loop_secs(stream, start, end));
  return 1;
}

static const luaL_reg allua_stream_methods[] = {
	{"create", allua_stream_create},
	{"from_file", allua_stream_from_file},
	{"rewind", allua_stream_rewind},
	{"get_frequency", allua_stream_get_frequency},
	{"get_channels", allua_stream_get_channels},
	{"get_depth", allua_stream_get_depth},
	{"get_length", allua_stream_get_length},
	{"get_speed", allua_stream_get_speed},
	{"set_speed", allua_stream_set_speed},
	{"get_gain", allua_stream_get_gain},
	{"set_gain", allua_stream_set_gain},
	{"get_pan", allua_stream_get_pan},
	{"set_pan", allua_stream_set_pan},
	{"get_playing", allua_stream_get_playing},
	{"set_playing", allua_stream_set_playing},
	{"get_playmode", allua_stream_get_playmode},
	{"set_playmode", allua_stream_set_playmode},
	{"get_attached", allua_stream_get_attached},
	{"detach", allua_stream_detach},
	{"seek_secs", allua_stream_seek_secs},
	{"get_position_secs", allua_stream_get_position_secs},
	{"get_length_secs", allua_stream_get_length_secs},
	{"set_loop_secs", allua_stream_set_loop_secs},
	{0,0}
};

/* GC and meta
 * */
static int allua_stream_gc (lua_State *L)
{
  struct ALLUA_stream_s *pi = (struct ALLUA_stream_s*)lua_touserdata(L, 1);
  if(pi->gc_allowed)
  {
	  ALLUA_stream im = pi->stream;
	  printf("goodbye stream (%p)\n", im);
	  if (im) al_destroy_stream(im);
  }
  return 0;
}

static int allua_stream_tostring (lua_State *L)
{
  lua_pushfstring(L, "stream: %p", lua_touserdata(L, 1));
  return 1;
}

static const luaL_reg allua_stream_meta[] = {
  {"__gc",       allua_stream_gc},
  {"__tostring", allua_stream_tostring},
  {0, 0}
};

/* Other attributes
 * */
void allua_stream_set_attributes(lua_State *L)
{
}

/* Register
 * */
int allua_register_stream (lua_State *L)
{
  lua_newtable (L);
  luaL_register(L, NULL, allua_stream_methods);  /* create methods table,
                                                add it to the globals */

	allua_stream_set_attributes(L);

  luaL_newmetatable(L, STREAM_STRING);        /* create metatable for Image,
                                         add it to the Lua registry */
  luaL_register(L, 0, allua_stream_meta);  /* fill metatable */
  lua_pushliteral(L, "__index");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* metatable.__index = methods */
  lua_pushliteral(L, "__metatable");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* hide metatable:
                                         metatable.__metatable = methods */
  lua_pop(L, 1);                      /* drop metatable */

  lua_setfield(L, -2, STREAM_STRING);

  return 0;                           /* return methods on the stack */
}
