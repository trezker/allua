#include "../include/allua/fs_entry.h"
#include "../include/allua/path.h"
#include "../include/allua/color.h"
#include "../include/allua/allua.h"
#include <stdio.h>
#include <allegro5/allegro_image.h>

#define FS_ENTRY_STRING "fs_entry"

/* Common handlers
 * */
/*static ALLUA_fs_entry toFs_entry (lua_State *L, int index)//, int *gc_allowed)
{
  struct ALLUA_fs_entry_s *pi = (struct ALLUA_fs_entry_s*)lua_touserdata(L, index);
  if (pi == NULL) luaL_typerror(L, index, FS_ENTRY_STRING);
//  if(gc_allowed)
//  	*gc_allowed = pi->gc_allowed;
  return pi->fs_entry;
}
*/
ALLUA_fs_entry allua_check_fs_entry (lua_State *L, int index)//, int *gc_allowed)
{
  struct ALLUA_fs_entry_s *pi;
  ALLUA_fs_entry im;
  luaL_checktype(L, index, LUA_TUSERDATA);
  pi = (struct ALLUA_fs_entry_s*)luaL_checkudata(L, index, FS_ENTRY_STRING);
  if (pi == NULL)
  	luaL_typerror(L, index, FS_ENTRY_STRING);
  im = pi->fs_entry;
  if (!im)
    luaL_error(L, "null fs_entry");
  return im;
}

struct ALLUA_fs_entry_s *allua_pushFs_entry (lua_State *L, ALLUA_fs_entry im, int gc_allowed)
{
	if(!im)
	{
		lua_pushnil(L);
		return NULL;
	}
	struct ALLUA_fs_entry_s *pi = (struct ALLUA_fs_entry_s *)lua_newuserdata(L, sizeof(struct ALLUA_fs_entry_s));
	pi->fs_entry = im;
	pi->gc_allowed = gc_allowed;
	luaL_getmetatable(L, FS_ENTRY_STRING);
	lua_setmetatable(L, -2);
	return pi;
}

/* Constructor and methods
 * */

static int allua_Fs_entry_create (lua_State *L)
{
	const char* path = luaL_checkstring(L, 1);

	ALLUA_fs_entry fs_entry = al_create_fs_entry(path);
	allua_pushFs_entry(L, fs_entry, true);

	return 1;
}

static int allua_Fs_entry_get_name (lua_State *L)
{
  ALLUA_fs_entry entry = allua_check_fs_entry(L, 1);

  ALLUA_path path = al_get_fs_entry_name(entry);
  allua_pushPath(L, path, false);

  return 1;
}

static int allua_Fs_entry_update (lua_State *L)
{
  ALLUA_fs_entry entry = allua_check_fs_entry(L, 1);

  lua_pushboolean(L, al_update_fs_entry(entry));

  return 1;
}

static int allua_Fs_entry_get_mode (lua_State *L)
{
  ALLUA_fs_entry entry = allua_check_fs_entry(L, 1);

  lua_pushnumber(L, al_get_fs_entry_mode(entry));

  return 1;
}

static int allua_Fs_entry_get_atime (lua_State *L)
{
  ALLUA_fs_entry entry = allua_check_fs_entry(L, 1);
  lua_pushnumber(L, al_get_fs_entry_atime(entry));
  return 1;
}

static int allua_Fs_entry_get_ctime (lua_State *L)
{
  ALLUA_fs_entry entry = allua_check_fs_entry(L, 1);
  lua_pushnumber(L, al_get_fs_entry_ctime(entry));
  return 1;
}

static int allua_Fs_entry_get_mtime (lua_State *L)
{
  ALLUA_fs_entry entry = allua_check_fs_entry(L, 1);
  lua_pushnumber(L, al_get_fs_entry_mtime(entry));
  return 1;
}

static int allua_Fs_entry_get_size (lua_State *L)
{
  ALLUA_fs_entry entry = allua_check_fs_entry(L, 1);
  lua_pushnumber(L, al_get_fs_entry_size(entry));
  return 1;
}

static int allua_Fs_entry_exists (lua_State *L)
{
  ALLUA_fs_entry entry = allua_check_fs_entry(L, 1);
  lua_pushboolean(L, al_fs_entry_exists(entry));
  return 1;
}
/*
static int allua_Fs_entry_is_file (lua_State *L)
{
  ALLUA_fs_entry entry = allua_check_fs_entry(L, 1);
  lua_pushboolean(L, al_is_fs_entry_file(entry));
  return 1;
}
static int allua_Fs_entry_is_directory (lua_State *L)
{
  ALLUA_fs_entry entry = allua_check_fs_entry(L, 1);
  lua_pushboolean(L, al_fs_entry_is_directory(entry));
  return 1;
}
*/

static int allua_Fs_entry_remove (lua_State *L)
{
  ALLUA_fs_entry entry = allua_check_fs_entry(L, 1);
  lua_pushboolean(L, al_remove_fs_entry(entry));
  return 1;
}

static int allua_Fs_entry_open_directory (lua_State *L)
{
  ALLUA_fs_entry entry = allua_check_fs_entry(L, 1);
  lua_pushboolean(L, al_open_directory(entry));
  return 1;
}

static int allua_Fs_entry_close_directory (lua_State *L)
{
  ALLUA_fs_entry entry = allua_check_fs_entry(L, 1);
  lua_pushboolean(L, al_close_directory(entry));
  return 1;
}

static int allua_Fs_entry_read_directory (lua_State *L)
{
  ALLUA_fs_entry entry = allua_check_fs_entry(L, 1);
  allua_pushFs_entry(L, al_read_directory(entry), true);
  return 1;
}
/*
ALLEGRO_FILE *al_open_fs_entry(ALLEGRO_FS_ENTRY *e, const char *mode)


*/

static const luaL_reg allua_Fs_entry_methods[] = {
	{"create",	allua_Fs_entry_create},
	{"get_name",	allua_Fs_entry_get_name},
	{"update",	allua_Fs_entry_update},
	{"get_mode",	allua_Fs_entry_get_mode},
	{"get_atime",	allua_Fs_entry_get_atime},
	{"get_ctime",	allua_Fs_entry_get_ctime},
	{"get_mtime",	allua_Fs_entry_get_mtime},
	{"get_size",	allua_Fs_entry_get_size},
	{"exists",	allua_Fs_entry_exists},
//	{"is_file",	allua_Fs_entry_is_file},
//	{"is_directory",	allua_Fs_entry_is_directory},
	{"remove",	allua_Fs_entry_remove},
	{"open_directory",	allua_Fs_entry_open_directory},
	{"close_directory",	allua_Fs_entry_close_directory},
	{"read_directory",	allua_Fs_entry_read_directory},
	{0,0}
};

/* GC and meta
 * */
static int allua_Fs_entry_gc (lua_State *L)
{
  struct ALLUA_fs_entry_s *pi = (struct ALLUA_fs_entry_s*)lua_touserdata(L, 1);
  if(pi->gc_allowed)
  {
	  ALLUA_fs_entry im = pi->fs_entry;
	  printf("goodbye fs_entry (%p)\n", im);
	  if (im) al_destroy_fs_entry(im);
  }
  return 0;
}

static int allua_Fs_entry_tostring (lua_State *L)
{
  lua_pushfstring(L, "fs_entry: %p", lua_touserdata(L, 1));
  return 1;
}

static const luaL_reg allua_Fs_entry_meta[] = {
  {"__gc",       allua_Fs_entry_gc},
  {"__tostring", allua_Fs_entry_tostring},
  {0, 0}
};

/* Other attributes
 * */
void allua_Fs_entry_set_attributes(lua_State *L)
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
int allua_register_fs_entry (lua_State *L)
{
  lua_newtable (L);
  luaL_register(L, NULL, allua_Fs_entry_methods);  /* create methods table,
                                                add it to the globals */

	allua_Fs_entry_set_attributes(L);

  luaL_newmetatable(L, FS_ENTRY_STRING);        /* create metatable for Image,
                                         add it to the Lua registry */
  luaL_register(L, 0, allua_Fs_entry_meta);  /* fill metatable */
  lua_pushliteral(L, "__index");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* metatable.__index = methods */
  lua_pushliteral(L, "__metatable");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* hide metatable:
                                         metatable.__metatable = methods */
  lua_pop(L, 1);                      /* drop metatable */

  lua_setfield(L, -2, FS_ENTRY_STRING);

  return 0;                           /* return methods on the stack */
}
