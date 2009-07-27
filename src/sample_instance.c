#include "allua/sample_instance.h"
#include "allua/sample.h"
#include <allegro5/acodec.h>
#include <stdio.h>

#define SAMPLE_INSTANCE_STRING "sample_instance"

/* Common handlers
 * */
/*static ALLUA_sample_instance tosample_instance (lua_State *L, int index)//, int *gc_allowed)
{
  struct ALLUA_sample_instance_s *pi = (struct ALLUA_sample_instance_s*)lua_touserdata(L, index);
  if (pi == NULL) luaL_typerror(L, index, SAMPLE_INSTANCE_STRING);
//  if(gc_allowed)
//  	*gc_allowed = pi->gc_allowed;
  return pi->sample_instance;
}
*/
ALLUA_sample_instance allua_check_sample_instance (lua_State *L, int index)//, int *gc_allowed)
{
  struct ALLUA_sample_instance_s *pi;
  ALLUA_sample_instance im;
  luaL_checktype(L, index, LUA_TUSERDATA);
  pi = (struct ALLUA_sample_instance_s*)luaL_checkudata(L, index, SAMPLE_INSTANCE_STRING);
  if (pi == NULL)
  	luaL_typerror(L, index, SAMPLE_INSTANCE_STRING);
  im = pi->sample_instance;
//  if(gc_allowed)
//  	*gc_allowed = pi->gc_allowed;
  if (!im)
    luaL_error(L, "null sample_instance");
  return im;
}

struct ALLUA_sample_instance_s *allua_pushsample_instance (lua_State *L, ALLUA_sample_instance im, int gc_allowed)
{
  struct ALLUA_sample_instance_s *pi = (struct ALLUA_sample_instance_s *)lua_newuserdata(L, sizeof(struct ALLUA_sample_instance_s));
  pi->sample_instance = im;
  pi->gc_allowed = gc_allowed;
  luaL_getmetatable(L, SAMPLE_INSTANCE_STRING);
  lua_setmetatable(L, -2);
  return pi;
}

/* Constructor and methods
 * */
static int allua_sample_instance_play (lua_State *L)
{
  ALLUA_sample_instance si = allua_check_sample_instance(L, 1);
  lua_pushboolean(L, al_play_sample_instance(si));
  return 1;
}

static int allua_sample_instance_stop (lua_State *L)
{
  ALLUA_sample_instance si = allua_check_sample_instance(L, 1);
  lua_pushboolean(L, al_stop_sample_instance(si));
  return 1;
}

static int allua_sample_instance_detach (lua_State *L)
{
  ALLUA_sample_instance si = allua_check_sample_instance(L, 1);
  lua_pushboolean(L, al_detach_sample_instance(si));
  return 1;
}

static int allua_sample_instance_set_sample (lua_State *L)
{
  ALLUA_sample_instance si = allua_check_sample_instance(L, 1);
  ALLUA_sample s = allua_check_sample(L, 2);
  lua_pushboolean(L, al_set_sample(si, s));
  return 1;
}

static int allua_sample_instance_get_sample (lua_State *L)
{
  ALLUA_sample_instance si = allua_check_sample_instance(L, 1);
  ALLUA_sample s = al_get_sample(si);
  if(s)
    allua_pushsample(L, s, false);
  else
    lua_pushnil(L);
  return 1;
}

static int allua_sample_instance_get_channels (lua_State *L)
{
  ALLUA_sample_instance si = allua_check_sample_instance(L, 1);
  lua_pushnumber(L, al_get_sample_instance_channels(si));
  return 1;
}

static int allua_sample_instance_get_depth (lua_State *L)
{
  ALLUA_sample_instance si = allua_check_sample_instance(L, 1);
  lua_pushnumber(L, al_get_sample_instance_depth(si));
  return 1;
}

static int allua_sample_instance_get_frequency (lua_State *L)
{
  ALLUA_sample_instance si = allua_check_sample_instance(L, 1);
  lua_pushnumber(L, al_get_sample_instance_frequency(si));
  return 1;
}

static int allua_sample_instance_get_length (lua_State *L)
{
  ALLUA_sample_instance si = allua_check_sample_instance(L, 1);
  lua_pushnumber(L, al_get_sample_instance_length(si));
  return 1;
}

static int allua_sample_instance_set_length (lua_State *L)
{
  ALLUA_sample_instance si = allua_check_sample_instance(L, 1);
  unsigned long val = luaL_checkint(L, 2);
  lua_pushboolean(L, al_set_sample_instance_length(si, val));
  return 1;
}

static int allua_sample_instance_get_position (lua_State *L)
{
  ALLUA_sample_instance si = allua_check_sample_instance(L, 1);
  lua_pushnumber(L, al_get_sample_instance_position(si));
  return 1;
}

static int allua_sample_instance_set_position (lua_State *L)
{
  ALLUA_sample_instance si = allua_check_sample_instance(L, 1);
  unsigned long val = luaL_checkint(L, 2);
  lua_pushboolean(L, al_set_sample_instance_position(si, val));
  return 1;
}

static int allua_sample_instance_get_speed (lua_State *L)
{
  ALLUA_sample_instance si = allua_check_sample_instance(L, 1);
  lua_pushnumber(L, al_get_sample_instance_speed(si));
  return 1;
}

static int allua_sample_instance_set_speed (lua_State *L)
{
  ALLUA_sample_instance si = allua_check_sample_instance(L, 1);
  float val = luaL_checknumber(L, 2);
  lua_pushboolean(L, al_set_sample_instance_speed(si, val));
  return 1;
}

static int allua_sample_instance_get_gain (lua_State *L)
{
  ALLUA_sample_instance si = allua_check_sample_instance(L, 1);
  lua_pushnumber(L, al_get_sample_instance_gain(si));
  return 1;
}

static int allua_sample_instance_set_gain (lua_State *L)
{
  ALLUA_sample_instance si = allua_check_sample_instance(L, 1);
  float val = luaL_checknumber(L, 2);
  lua_pushboolean(L, al_set_sample_instance_gain(si, val));
  return 1;
}

static int allua_sample_instance_get_pan (lua_State *L)
{
  ALLUA_sample_instance si = allua_check_sample_instance(L, 1);
  lua_pushnumber(L, al_get_sample_instance_pan(si));
  return 1;
}

static int allua_sample_instance_set_pan (lua_State *L)
{
  ALLUA_sample_instance si = allua_check_sample_instance(L, 1);
  float val = luaL_checknumber(L, 2);
  lua_pushboolean(L, al_set_sample_instance_pan(si, val));
  return 1;
}

static int allua_sample_instance_get_time (lua_State *L)
{
  ALLUA_sample_instance si = allua_check_sample_instance(L, 1);
  lua_pushnumber(L, al_get_sample_instance_time(si));
  return 1;
}

static int allua_sample_instance_get_playmode (lua_State *L)
{
  ALLUA_sample_instance si = allua_check_sample_instance(L, 1);
  lua_pushnumber(L, al_get_sample_instance_playmode(si));
  return 1;
}

static int allua_sample_instance_set_playmode (lua_State *L)
{
  ALLUA_sample_instance si = allua_check_sample_instance(L, 1);
  int mode = luaL_checkint(L, 2);
  lua_pushboolean(L, al_set_sample_instance_playmode(si, mode));
  return 1;
}

static int allua_sample_instance_get_playing (lua_State *L)
{
  ALLUA_sample_instance si = allua_check_sample_instance(L, 1);
  lua_pushboolean(L, al_get_sample_instance_playing(si));
  return 1;
}

static int allua_sample_instance_set_playing (lua_State *L)
{
  ALLUA_sample_instance si = allua_check_sample_instance(L, 1);
  bool v = lua_toboolean(L, 2);
  lua_pushboolean(L, al_set_sample_instance_playing(si, v));
  return 1;
}

static int allua_sample_instance_get_attached (lua_State *L)
{
  ALLUA_sample_instance si = allua_check_sample_instance(L, 1);
  lua_pushboolean(L, al_get_sample_instance_attached(si));
  return 1;
}

static const luaL_reg allua_sample_instance_methods[] = {
	{"play", allua_sample_instance_play},
	{"stop", allua_sample_instance_stop},
	{"detach", allua_sample_instance_detach},
	{"get_channels", allua_sample_instance_get_channels},
	{"get_depth", allua_sample_instance_get_depth},
	{"get_frequency", allua_sample_instance_get_frequency},
	{"get_length", allua_sample_instance_get_length},
	{"set_length", allua_sample_instance_set_length},
	{"get_position", allua_sample_instance_get_position},
	{"set_position", allua_sample_instance_set_position},
	{"get_speed", allua_sample_instance_get_speed},
	{"set_speed", allua_sample_instance_set_speed},
	{"get_gain", allua_sample_instance_get_gain},
	{"set_gain", allua_sample_instance_set_gain},
	{"get_pan", allua_sample_instance_get_pan},
	{"set_pan", allua_sample_instance_set_pan},
	{"get_time", allua_sample_instance_get_time},
	{"get_playmode", allua_sample_instance_get_playmode},
	{"set_playmode", allua_sample_instance_set_playmode},
	{"get_playing", allua_sample_instance_get_playing},
	{"set_playing", allua_sample_instance_set_playing},
	{"get_attached", allua_sample_instance_get_attached},
	{"get_sample", allua_sample_instance_get_sample},
	{"set_sample", allua_sample_instance_set_sample},
	{0,0}
};

/* GC and meta
 * */
static int allua_sample_instance_gc (lua_State *L)
{
  struct ALLUA_sample_instance_s *pi = (struct ALLUA_sample_instance_s*)lua_touserdata(L, 1);
  if(pi->gc_allowed)
  {
	  ALLUA_sample_instance im = pi->sample_instance;
	  printf("goodbye sample_instance (%p)\n", pi);
	  if (im) al_destroy_sample_instance(im);
  }
  return 0;
}

static int allua_sample_instance_tostring (lua_State *L)
{
  lua_pushfstring(L, "sample_instance: %p", lua_touserdata(L, 1));
  return 1;
}

static const luaL_reg allua_sample_instance_meta[] = {
  {"__gc",       allua_sample_instance_gc},
  {"__tostring", allua_sample_instance_tostring},
  {0, 0}
};

/* Other attributes
 * */
void allua_sample_instance_set_attributes(lua_State *L)
{
//	lua_pushinteger(L, ALLEGRO_MEMORY_SAMPLE_INSTANCE);
//	lua_setfield(L, -2, "MEMORY_SAMPLE_INSTANCE");
}

/* Register
 * */
int allua_register_sample_instance (lua_State *L)
{
  lua_newtable (L);
  luaL_register(L, NULL, allua_sample_instance_methods);  /* create methods table,
                                                add it to the globals */

	allua_sample_instance_set_attributes(L);

  luaL_newmetatable(L, SAMPLE_INSTANCE_STRING);        /* create metatable for Image,
                                         add it to the Lua registry */
  luaL_register(L, 0, allua_sample_instance_meta);  /* fill metatable */
  lua_pushliteral(L, "__index");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* metatable.__index = methods */
  lua_pushliteral(L, "__metatable");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* hide metatable:
                                         metatable.__metatable = methods */
  lua_pop(L, 1);                      /* drop metatable */

  lua_setfield(L, -2, SAMPLE_INSTANCE_STRING);

  return 0;                           /* return methods on the stack */
}
