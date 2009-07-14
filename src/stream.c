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
//  if(gc_allowed)
//  	*gc_allowed = pi->gc_allowed;
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

static const luaL_reg allua_stream_methods[] = {
	{"create", allua_stream_create},
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
//	lua_pushinteger(L, ALLEGRO_MEMORY_STREAM);
//	lua_setfield(L, -2, "MEMORY_STREAM");
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
