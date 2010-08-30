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
	if(!im)
	{
	  	lua_pushnil(L);
	  	return NULL;
	}
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
	allua_pushPath(L, path, true);

	return 1;
}

static int allua_Path_create_for_directory (lua_State *L)
{
	const char* str = luaL_checkstring(L, 1);

	ALLUA_path path = al_create_path_for_directory(str);
	allua_pushPath(L, path, true);

	return 1;
}

static int allua_Path_clone (lua_State *L)
{
	ALLUA_path path = allua_check_path(L, 1);

	ALLUA_path clone = al_clone_path(path);
	allua_pushPath(L, clone, true);

	return 1;
}

static int allua_Path_join (lua_State *L)
{
	ALLUA_path path = allua_check_path(L, 1);
	ALLUA_path tail = allua_check_path(L, 2);

	lua_pushboolean(L, al_join_paths(path, tail));

	return 1;
}

static int allua_Path_get_drive (lua_State *L)
{
	ALLUA_path path = allua_check_path(L, 1);

	lua_pushstring(L, al_get_path_drive(path));

	return 1;
}

static int allua_Path_get_num_components (lua_State *L)
{
	ALLUA_path path = allua_check_path(L, 1);

	lua_pushnumber(L, al_get_path_num_components(path));

	return 1;
}

static int allua_Path_get_component (lua_State *L)
{
	ALLUA_path path = allua_check_path(L, 1);
	int i = luaL_checkint(L, 2);

	lua_pushstring(L, al_get_path_component(path, i));

	return 1;
}

static int allua_Path_get_tail (lua_State *L)
{
	ALLUA_path path = allua_check_path(L, 1);

	lua_pushstring(L, al_get_path_tail(path));

	return 1;
}

static int allua_Path_get_filename (lua_State *L)
{
	ALLUA_path path = allua_check_path(L, 1);

	lua_pushstring(L, al_get_path_filename(path));

	return 1;
}

static int allua_Path_get_basename (lua_State *L)
{
	ALLUA_path path = allua_check_path(L, 1);

	lua_pushstring(L, al_get_path_basename(path));

	return 1;
}

static int allua_Path_get_extension (lua_State *L)
{
	ALLUA_path path = allua_check_path(L, 1);

	lua_pushstring(L, al_get_path_extension(path));

	return 1;
}

static int allua_Path_set_drive (lua_State *L)
{
	ALLUA_path path = allua_check_path(L, 1);
	const char* drive = luaL_checkstring(L, 2);

	al_set_path_drive(path, drive);

	return 0;
}

static int allua_Path_append_component (lua_State *L)
{
	ALLUA_path path = allua_check_path(L, 1);
	const char* s = luaL_checkstring(L, 2);

	al_append_path_component(path, s);

	return 0;
}

static int allua_Path_insert_component (lua_State *L)
{
	ALLUA_path path = allua_check_path(L, 1);
	int i = luaL_checkint(L, 2);
	const char* s = luaL_checkstring(L, 3);

	al_insert_path_component(path, i, s);

	return 0;
}

static int allua_Path_replace_component (lua_State *L)
{
	ALLUA_path path = allua_check_path(L, 1);
	int i = luaL_checkint(L, 2);
	const char* s = luaL_checkstring(L, 3);

	al_replace_path_component(path, i, s);

	return 0;
}

static int allua_Path_remove_component (lua_State *L)
{
	ALLUA_path path = allua_check_path(L, 1);
	int i = luaL_checkint(L, 2);

	al_remove_path_component(path, i);

	return 0;
}

static int allua_Path_drop_tail (lua_State *L)
{
	ALLUA_path path = allua_check_path(L, 1);

	al_drop_path_tail(path);

	return 0;
}

static int allua_Path_set_filename (lua_State *L)
{
	ALLUA_path path = allua_check_path(L, 1);
	const char* s = luaL_checkstring(L, 2);

	al_set_path_filename(path, s);

	return 0;
}

static int allua_Path_set_extension (lua_State *L)
{
	ALLUA_path path = allua_check_path(L, 1);
	const char* s = luaL_checkstring(L, 2);

	lua_pushboolean(L, al_set_path_extension(path, s));

	return 1;
}

static int allua_Path_get_string (lua_State *L)
{
	ALLUA_path path = allua_check_path(L, 1);
	lua_pushstring(L, al_path_cstr(path, ALLEGRO_NATIVE_PATH_SEP));

	return 1;
}

static int allua_Path_make_absolute (lua_State *L)
{
	ALLUA_path path = allua_check_path(L, 1);
	lua_pushboolean(L, al_make_path_absolute(path));

	return 1;
}

static int allua_Path_make_canonical (lua_State *L)
{
	ALLUA_path path = allua_check_path(L, 1);
	lua_pushboolean(L, al_make_path_canonical(path));

	return 1;
}

static int allua_Path_is_present (lua_State *L)
{
	ALLUA_path path = allua_check_path(L, 1);
	lua_pushboolean(L, al_is_path_present(path));

	return 1;
}

static int allua_Path_get_current_directory (lua_State *L)
{
	allua_pushPath(L, al_get_current_directory(), true);
	return 1;
}

static const luaL_reg allua_Path_methods[] = {
	{"create",	allua_Path_create},
	{"create_for_directory",	allua_Path_create_for_directory},
	{"clone",	allua_Path_clone},
	{"join",	allua_Path_join},
	{"get_drive",	allua_Path_get_drive},
	{"get_num_components",	allua_Path_get_num_components},
	{"get_component",	allua_Path_get_component},
	{"get_tail",	allua_Path_get_tail},
	{"get_filename",	allua_Path_get_filename},
	{"get_basename",	allua_Path_get_basename},
	{"get_extension",	allua_Path_get_extension},
	{"set_drive",	allua_Path_set_drive},
	{"append_component",	allua_Path_append_component},
	{"insert_component",	allua_Path_insert_component},
	{"replace_component",	allua_Path_replace_component},
	{"remove_component",	allua_Path_remove_component},
	{"drop_tail",	allua_Path_drop_tail},
	{"set_filename",	allua_Path_set_filename},
	{"set_extension",	allua_Path_set_extension},
	{"get_string",	allua_Path_get_string},
	{"make_absolute",	allua_Path_make_absolute},
	{"make_canonical",	allua_Path_make_canonical},
	{"is_present",	allua_Path_is_present},
	{"get_current_directory",	allua_Path_get_current_directory},
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
