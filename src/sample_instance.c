#include "allua/sample_instance.h"
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

static int allua_sample_instance_get_channels (lua_State *L)
{
  ALLUA_sample_instance si = allua_check_sample_instance(L, 1);
  lua_pushnumber(L, al_get_sample_instance_channels(si));
  return 1;
}

static const luaL_reg allua_sample_instance_methods[] = {
	{"play", allua_sample_instance_play},
	{"stop", allua_sample_instance_stop},
	{"get_channels", allua_sample_instance_get_channels},
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
	  printf("goodbye sample_instance (%p)\n", im);
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
