#include "allua/mixer.h"
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
ALLUA_mixer allua_check_mixer (lua_State *L, int index)//, int *gc_allowed)
{
  struct ALLUA_mixer_s *pi;
  ALLUA_mixer im;
  luaL_checktype(L, index, LUA_TUSERDATA);
  pi = (struct ALLUA_mixer_s*)luaL_checkudata(L, index, MIXER_STRING);
  if (pi == NULL)
  	luaL_typerror(L, index, MIXER_STRING);
  im = pi->mixer;
//  if(gc_allowed)
//  	*gc_allowed = pi->gc_allowed;
  if (!im)
    luaL_error(L, "null mixer");
  return im;
}

struct ALLUA_mixer_s *allua_pushmixer (lua_State *L, ALLUA_mixer im, int gc_allowed)
{
  struct ALLUA_mixer_s *pi = (struct ALLUA_mixer_s *)lua_newuserdata(L, sizeof(struct ALLUA_mixer_s));
  pi->mixer = im;
  pi->gc_allowed = gc_allowed;
  luaL_getmetatable(L, MIXER_STRING);
  lua_setmetatable(L, -2);
  return pi;
}

/* Constructor and methods
 * */

static int allua_mixer_create (lua_State *L)
{
  int freq = luaL_checkint(L, 1);
  int depth = luaL_checkint(L, 2);
  int chan_conf = luaL_checkint(L, 3);
	ALLUA_mixer mixer = al_create_mixer(freq, depth, chan_conf);
	if(mixer)
  		allua_pushmixer(L, mixer, true);
	else
		lua_pushnil(L);

  return 1;
}

static const luaL_reg allua_mixer_methods[] = {
	{"create", allua_mixer_create},
	{0,0}
};

/* GC and meta
 * */
static int allua_mixer_gc (lua_State *L)
{
  struct ALLUA_mixer_s *pi = (struct ALLUA_mixer_s*)lua_touserdata(L, 1);
  if(pi->gc_allowed)
  {
	  ALLUA_mixer im = pi->mixer;
	  printf("goodbye mixer (%p)\n", im);
	  if (im) al_destroy_mixer(im);
  }
  return 0;
}

static int allua_mixer_tostring (lua_State *L)
{
  lua_pushfstring(L, "mixer: %p", lua_touserdata(L, 1));
  return 1;
}

static const luaL_reg allua_mixer_meta[] = {
  {"__gc",       allua_mixer_gc},
  {"__tostring", allua_mixer_tostring},
  {0, 0}
};

/* Other attributes
 * */
void allua_mixer_set_attributes(lua_State *L)
{
//	lua_pushinteger(L, ALLEGRO_MEMORY_MIXER);
//	lua_setfield(L, -2, "MEMORY_MIXER");
}

/* Register
 * */
int allua_register_mixer (lua_State *L)
{
  lua_newtable (L);
  luaL_register(L, NULL, allua_mixer_methods);  /* create methods table,
                                                add it to the globals */

	allua_mixer_set_attributes(L);

  luaL_newmetatable(L, MIXER_STRING);        /* create metatable for Image,
                                         add it to the Lua registry */
  luaL_register(L, 0, allua_mixer_meta);  /* fill metatable */
  lua_pushliteral(L, "__index");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* metatable.__index = methods */
  lua_pushliteral(L, "__metatable");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* hide metatable:
                                         metatable.__metatable = methods */
  lua_pop(L, 1);                      /* drop metatable */

  lua_setfield(L, -2, MIXER_STRING);

  return 0;                           /* return methods on the stack */
}
