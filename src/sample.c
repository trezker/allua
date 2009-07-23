#include "allua/sample.h"
#include "allua/sample_id.h"
#include "allua/sample_instance.h"
#include <allegro5/acodec.h>
#include <stdio.h>

#define SAMPLE_STRING "sample"

/* Common handlers
 * */
/*static ALLUA_sample tosample (lua_State *L, int index)//, int *gc_allowed)
{
  struct ALLUA_sample_s *pi = (struct ALLUA_sample_s*)lua_touserdata(L, index);
  if (pi == NULL) luaL_typerror(L, index, SAMPLE_STRING);
//  if(gc_allowed)
//  	*gc_allowed = pi->gc_allowed;
  return pi->sample;
}
*/
ALLUA_sample allua_check_sample (lua_State *L, int index)//, int *gc_allowed)
{
  struct ALLUA_sample_s *pi;
  ALLUA_sample im;
  luaL_checktype(L, index, LUA_TUSERDATA);
  pi = (struct ALLUA_sample_s*)luaL_checkudata(L, index, SAMPLE_STRING);
  if (pi == NULL)
  	luaL_typerror(L, index, SAMPLE_STRING);
  im = pi->sample;
//  if(gc_allowed)
//  	*gc_allowed = pi->gc_allowed;
  if (!im)
    luaL_error(L, "null sample");
  return im;
}

struct ALLUA_sample_s *allua_pushsample (lua_State *L, ALLUA_sample im, int gc_allowed)
{
  struct ALLUA_sample_s *pi = (struct ALLUA_sample_s *)lua_newuserdata(L, sizeof(struct ALLUA_sample_s));
  pi->sample = im;
  pi->gc_allowed = gc_allowed;
  luaL_getmetatable(L, SAMPLE_STRING);
  lua_setmetatable(L, -2);
  return pi;
}

/* Constructor and methods
 * */

static int allua_sample_load (lua_State *L)
{
	const char* filename = luaL_checkstring(L, 1);
	ALLUA_sample sample = al_load_sample(filename);
	if(sample)
		allua_pushsample(L, sample, true);
	else
		lua_pushnil(L);

	return 1;
}

static int allua_sample_save (lua_State *L)
{
	ALLUA_sample sample = allua_check_sample(L, 1);
	const char* filename = luaL_checkstring(L, 2);
	lua_pushboolean(L, al_save_sample(sample, filename));
	return 1;
}

static int allua_sample_play (lua_State *L)
{
	ALLUA_sample spl = allua_check_sample(L, 1);
	float gain = luaL_checknumber(L, 2);
	float pan = luaL_checknumber(L, 3);
	float speed = luaL_checknumber(L, 4);
	int loop = luaL_checkint(L, 5);
	ALLEGRO_SAMPLE_ID ret_id;
	int s = al_play_sample(spl, gain, pan, speed, loop, &ret_id);
	lua_pushboolean(L, s);
	if(s)
	{
		allua_pushsample_id(L, ret_id);
		return 2;
	}
	return 1;
}

static int allua_sample_stop_samples (lua_State *L)
{
	al_stop_samples();
	return 0;
}

static int allua_sample_create_instance (lua_State *L)
{
	struct ALLUA_sample_s *pi = (struct ALLUA_sample_s*)(lua_touserdata(L, index));
	ALLUA_sample sample_data;
	if (pi == NULL) 
		sample_data = NULL;
	else
		sample_data = allua_check_sample(L, 1);
	ALLUA_sample_instance instance = al_create_sample_instance(sample_data);
	if(instance)
	{
		allua_pushsample_instance(L, instance, true);
	}
	else
	{
		lua_pushnil(L);
	}
	return 1;
}

static const luaL_reg allua_sample_methods[] = {
	{"load", allua_sample_load},
	{"save", allua_sample_save},
	{"play", allua_sample_play},
	{"stop_samples", allua_sample_stop_samples},
	{"create_instance", allua_sample_create_instance},
	{0,0}
};

/* GC and meta
 * */
static int allua_sample_gc (lua_State *L)
{
  struct ALLUA_sample_s *pi = (struct ALLUA_sample_s*)lua_touserdata(L, 1);
  if(pi->gc_allowed)
  {
	  ALLUA_sample im = pi->sample;
	  printf("goodbye sample (%p)\n", im);
//	  if (im) al_destroy_sample(im);
  }
  return 0;
}

static int allua_sample_tostring (lua_State *L)
{
  lua_pushfstring(L, "sample: %p", lua_touserdata(L, 1));
  return 1;
}

static const luaL_reg allua_sample_meta[] = {
  {"__gc",       allua_sample_gc},
  {"__tostring", allua_sample_tostring},
  {0, 0}
};

/* Other attributes
 * */
void allua_sample_set_attributes(lua_State *L)
{
//	lua_pushinteger(L, ALLEGRO_MEMORY_SAMPLE);
//	lua_setfield(L, -2, "MEMORY_SAMPLE");
}

/* Register
 * */
int allua_register_sample (lua_State *L)
{
  lua_newtable (L);
  luaL_register(L, NULL, allua_sample_methods);  /* create methods table,
                                                add it to the globals */

	allua_sample_set_attributes(L);

  luaL_newmetatable(L, SAMPLE_STRING);        /* create metatable for Image,
                                         add it to the Lua registry */
  luaL_register(L, 0, allua_sample_meta);  /* fill metatable */
  lua_pushliteral(L, "__index");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* metatable.__index = methods */
  lua_pushliteral(L, "__metatable");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* hide metatable:
                                         metatable.__metatable = methods */
  lua_pop(L, 1);                      /* drop metatable */

  lua_setfield(L, -2, SAMPLE_STRING);

  return 0;                           /* return methods on the stack */
}
