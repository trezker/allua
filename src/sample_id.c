#include "allua/sample_id.h"
#include <stdio.h>

#define SAMPLE_ID_STRING "sample_id"

/* Common handlers
 * */
/*static ALLUA_sample_id tosample_id (lua_State *L, int index)
{
  ALLUA_sample_id *pi = (ALLUA_sample_id*)lua_touserdata(L, index);
  if (pi == NULL) luaL_typerror(L, index, sample_id_STRING);
  return *pi;
}
*/
ALLUA_sample_id allua_check_sample_id (lua_State *L, int index)
{
  ALLUA_sample_id *pi, im;
  luaL_checktype(L, index, LUA_TUSERDATA);
  pi = (ALLUA_sample_id*)luaL_checkudata(L, index, SAMPLE_ID_STRING);
  if (pi == NULL)
  	luaL_typerror(L, index, SAMPLE_ID_STRING);
  im = *pi;
  return im;
}

ALLUA_sample_id *allua_pushsample_id (lua_State *L, ALLUA_sample_id im)
{
  ALLUA_sample_id *pi = (ALLUA_sample_id *)lua_newuserdata(L, sizeof(ALLUA_sample_id));
  *pi = im;
  luaL_getmetatable(L, SAMPLE_ID_STRING);
  lua_setmetatable(L, -2);
  return pi;
}

/* Constructor and methods
 * */
static int allua_sample_id_stop (lua_State *L)
{
	ALLUA_sample_id spl = allua_check_sample_id(L, 1);
	al_stop_sample(&spl);
	return 0;
}

static const luaL_reg allua_sample_id_methods[] = {
  {"stop",allua_sample_id_stop},
  {0,0}
};

/* GC and meta
 * */
static int allua_sample_id_tostring (lua_State *L)
{
  lua_pushfstring(L, "sample_id: %p", lua_touserdata(L, 1));
  return 1;
}

static const luaL_reg allua_sample_id_meta[] = {
  {"__tostring", allua_sample_id_tostring},
  {0, 0}
};

/* Register
 * */
int allua_register_sample_id (lua_State *L)
{
  lua_newtable(L);
  luaL_register(L, NULL, allua_sample_id_methods);  /* create methods table,
                                                add it to the globals */

  luaL_newmetatable(L, SAMPLE_ID_STRING);        /* create metatable for Image,
                                         add it to the Lua registry */
  luaL_register(L, 0, allua_sample_id_meta);  /* fill metatable */
  lua_pushliteral(L, "__index");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* metatable.__index = methods */
  lua_pushliteral(L, "__metatable");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* hide metatable:
                                         metatable.__metatable = methods */
  lua_pop(L, 1);                      /* drop metatable */

  lua_setfield(L, -2, SAMPLE_ID_STRING);
  return 0;                           /* return methods on the stack */
}
