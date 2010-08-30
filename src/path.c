#include "../include/allua/path.h"
#include "../include/allua/color.h"
#include "../include/allua/allua.h"
#include <stdio.h>
#include <allegro5/allegro_image.h>

#define PATH_STRING "path"

/* Common handlers
 * */
/*static ALLUA_path toPath (lua_State *L, int index)//, int *gc_allowed)
{
  struct ALLUA_path_s *pi = (struct ALLUA_path_s*)lua_touserdata(L, index);
  if (pi == NULL) luaL_typerror(L, index, PATH_STRING);
//  if(gc_allowed)
//  	*gc_allowed = pi->gc_allowed;
  return pi->path;
}
*/
ALLUA_path allua_check_path (lua_State *L, int index)//, int *gc_allowed)
{
  struct ALLUA_path_s *pi;
  ALLUA_path im;
  luaL_checktype(L, index, LUA_TUSERDATA);
  pi = (struct ALLUA_path_s*)luaL_checkudata(L, index, PATH_STRING);
  if (pi == NULL)
  	luaL_typerror(L, index, PATH_STRING);
  im = pi->path;
  if (!im)
    luaL_error(L, "null path");
  return im;
}

struct ALLUA_path_s *allua_pushPath (lua_State *L, ALLUA_path im, int gc_allowed)
{
  struct ALLUA_path_s *pi = (struct ALLUA_path_s *)lua_newuserdata(L, sizeof(struct ALLUA_path_s));
  pi->path = im;
  pi->gc_allowed = gc_allowed;
  luaL_getmetatable(L, PATH_STRING);
  lua_setmetatable(L, -2);
  return pi;
}

/* Constructor and methods
 * */

static int allua_Path_create (lua_State *L)
{
  const char* str = luaL_checkstring(L, 1);

  ALLUA_path path = al_create_path(str);
  if(path)
  	allua_pushPath(L, path, true);
  else
  	lua_pushnil(L);

  return 1;
}

static const luaL_reg allua_Path_methods[] = {
  {"create",           allua_Path_create},
  {0,0}
};

/* GC and meta
 * */
static int allua_Path_gc (lua_State *L)
{
  struct ALLUA_path_s *pi = (struct ALLUA_path_s*)lua_touserdata(L, 1);
  if(pi->gc_allowed)
  {
	  ALLUA_path im = pi->path;
	  printf("goodbye path (%p)\n", im);
	  if (im) al_destroy_path(im);
  }
  return 0;
}

static int allua_Path_tostring (lua_State *L)
{
  lua_pushfstring(L, "path: %p", lua_touserdata(L, 1));
  return 1;
}

static const luaL_reg allua_Path_meta[] = {
  {"__gc",       allua_Path_gc},
  {"__tostring", allua_Path_tostring},
  {0, 0}
};

/* Other attributes
 * */
void allua_Path_set_attributes(lua_State *L)
{
	lua_pushinteger(L, ALLEGRO_FILEMODE_READ);
	lua_setfield(L, -2, "FILEMODE_READ");
	lua_pushinteger(L, ALLEGRO_FILEMODE_WRITE);
	lua_setfield(L, -2, "FILEMODE_WRITE");
	lua_pushinteger(L, ALLEGRO_FILEMODE_EXECUTE);
	lua_setfield(L, -2, "FILEMODE_EXECUTE");
	lua_pushinteger(L, ALLEGRO_FILEMODE_HIDDEN);
	lua_setfield(L, -2, "FILEMODE_HIDDEN");
	lua_pushinteger(L, ALLEGRO_FILEMODE_ISFILE);
	lua_setfield(L, -2, "FILEMODE_ISFILE");
	lua_pushinteger(L, ALLEGRO_FILEMODE_ISDIR);
	lua_setfield(L, -2, "FILEMODE_ISDIR");
}

/* Register
 * */
int allua_register_path (lua_State *L)
{
  lua_newtable (L);
  luaL_register(L, NULL, allua_Path_methods);  /* create methods table,
                                                add it to the globals */

	allua_Path_set_attributes(L);

  luaL_newmetatable(L, PATH_STRING);        /* create metatable for Image,
                                         add it to the Lua registry */
  luaL_register(L, 0, allua_Path_meta);  /* fill metatable */
  lua_pushliteral(L, "__index");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* metatable.__index = methods */
  lua_pushliteral(L, "__metatable");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* hide metatable:
                                         metatable.__metatable = methods */
  lua_pop(L, 1);                      /* drop metatable */

  lua_setfield(L, -2, PATH_STRING);

  return 0;                           /* return methods on the stack */
}
