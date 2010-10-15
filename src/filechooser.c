#include "../include/allua/filechooser.h"
#include "../include/allua/display.h"
#include "../include/allua/allua.h"
#include <stdio.h>
#include <allegro5/allegro_native_dialog.h>

#define FILECHOOSER_STRING "filechooser"

/* Common handlers
 * */
static ALLUA_filechooser allua_toFilechooser (lua_State *L, int index)
{
  ALLUA_filechooser *pi = (ALLUA_filechooser*)lua_touserdata(L, index);
  if (pi == NULL) luaL_typerror(L, index, FILECHOOSER_STRING);
  return *pi;
}

ALLUA_filechooser allua_check_filechooser (lua_State *L, int index)
{
  ALLUA_filechooser *pi, im;
  luaL_checktype(L, index, LUA_TUSERDATA);
  pi = (ALLUA_filechooser*)luaL_checkudata(L, index, FILECHOOSER_STRING);
  if (pi == NULL)
  	luaL_typerror(L, index, FILECHOOSER_STRING);
  im = *pi;
  if (!im)
    luaL_error(L, "null Filechooser");
  return im;
}

static ALLUA_filechooser *allua_pushFilechooser (lua_State *L, ALLUA_filechooser im)
{
	if(!im)
	{
		lua_pushnil(L);
		return NULL;
	}
  ALLUA_filechooser *pi = (ALLUA_filechooser *)lua_newuserdata(L, sizeof(ALLUA_filechooser));
  *pi = im;
  luaL_getmetatable(L, FILECHOOSER_STRING);
  lua_setmetatable(L, -2);
  return pi;
}

/* Constructor and methods
 * */

static int allua_Filechooser_create (lua_State *L)
{
	const char* ipath = luaL_checkstring(L, 1);
	const char* title = luaL_checkstring(L, 2);
	const char* patterns = luaL_checkstring(L, 3);
	int mode = luaL_checkint(L, 4);
	ALLEGRO_PATH *initial_path = al_create_path(ipath);
	ALLUA_filechooser d = al_create_native_file_dialog(initial_path, title, patterns, mode);
	if(d)
		allua_pushFilechooser(L, d);
	else
		lua_pushnil(L);
	return 1;
}

static int allua_Filechooser_show (lua_State *L)
{
	ALLUA_filechooser d = allua_check_filechooser(L, 1);
	ALLUA_display display = NULL;
	if(!lua_isnoneornil(L, 2))
		display = allua_check_display(L, 2);
	al_show_native_file_dialog(display, d);
	return 0;
}

static int allua_Filechooser_get_count (lua_State *L)
{
	ALLUA_filechooser d = allua_check_filechooser(L, 1);
	lua_pushnumber(L, al_get_native_file_dialog_count(d));
	return 1;
}

static int allua_Filechooser_get_path (lua_State *L)
{
	ALLUA_filechooser d = allua_check_filechooser(L, 1);
	int i = luaL_checkint(L, 2);
	const ALLEGRO_PATH *path = al_get_native_file_dialog_path(d, i);
	lua_pushstring(L, al_path_cstr(path, ALLEGRO_NATIVE_PATH_SEP));
	return 1;
}

static const luaL_reg allua_Filechooser_methods[] = {
  {"create", allua_Filechooser_create},
  {"show", allua_Filechooser_show},
  {"get_count", allua_Filechooser_get_count},
  {"get_path", allua_Filechooser_get_path},
  {0,0}
};

/* GC and meta
 * */
static int allua_Filechooser_gc (lua_State *L)
{
  ALLUA_filechooser im = allua_toFilechooser(L, 1);
  printf("goodbye Filechooser (%p)\n", im);
  if (im) al_destroy_native_file_dialog(im);
  return 0;
}

static int allua_Filechooser_tostring (lua_State *L)
{
  lua_pushfstring(L, "filechooser: %p", lua_touserdata(L, 1));
  return 1;
}

static const luaL_reg allua_Filechooser_meta[] = {
  {"__gc",       allua_Filechooser_gc},
  {"__tostring", allua_Filechooser_tostring},
  {0, 0}
};

/* Other attributes
 * */
void allua_Filechooser_set_attributes(lua_State *L)
{
	lua_pushinteger(L, ALLEGRO_FILECHOOSER_FILE_MUST_EXIST);
	lua_setfield(L, -2, "FILECHOOSER_FILE_MUST_EXIST");
	lua_pushinteger(L, ALLEGRO_FILECHOOSER_SAVE);
	lua_setfield(L, -2, "FILECHOOSER_SAVE");
	lua_pushinteger(L, ALLEGRO_FILECHOOSER_FOLDER);
	lua_setfield(L, -2, "FILECHOOSER_FOLDER");
	lua_pushinteger(L, ALLEGRO_FILECHOOSER_PICTURES);
	lua_setfield(L, -2, "FILECHOOSER_PICTURES");
	lua_pushinteger(L, ALLEGRO_FILECHOOSER_SHOW_HIDDEN);
	lua_setfield(L, -2, "FILECHOOSER_SHOW_HIDDEN");
	lua_pushinteger(L, ALLEGRO_FILECHOOSER_MULTIPLE);
	lua_setfield(L, -2, "FILECHOOSER_MULTIPLE");
}

/* Register
 * */
int allua_register_filechooser (lua_State *L)
{
  lua_newtable (L);
  luaL_register(L, NULL, allua_Filechooser_methods);  /* create methods table,
                                                add it to the globals */

	allua_Filechooser_set_attributes(L);

  luaL_newmetatable(L, FILECHOOSER_STRING);        /* create metatable for Image,
                                         add it to the Lua registry */
  luaL_register(L, 0, allua_Filechooser_meta);  /* fill metatable */
  lua_pushliteral(L, "__index");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* metatable.__index = methods */
  lua_pushliteral(L, "__metatable");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* hide metatable:
                                         metatable.__metatable = methods */
  lua_pop(L, 1);                      /* drop metatable */

  lua_setfield(L, -2, FILECHOOSER_STRING);
	
  return 0;                           /* return methods on the stack */
}
