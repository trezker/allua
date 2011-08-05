#include "../include/allua/filesystem.h"
#include <allegro5/allegro.h>
#include <stdio.h>

#define FILESYSTEM_STRING "filesystem"

/* Methods
 * */
static int allua_make_directory(lua_State * L)
{
   const char *path = luaL_checkstring(L, 1);
   lua_pushboolean(L, al_make_directory(path));
   return 1;
}

static int allua_filename_exists(lua_State * L)
{
   const char *path = luaL_checkstring(L, 1);
   lua_pushboolean(L, al_filename_exists(path));
   return 1;
}

static int allua_remove_filename(lua_State * L)
{
   const char *path = luaL_checkstring(L, 1);
   lua_pushboolean(L, al_remove_filename(path));
   return 1;
}

static int allua_change_directory(lua_State * L)
{
   const char *path = luaL_checkstring(L, 1);
   lua_pushboolean(L, al_change_directory(path));
   return 1;
}

static const luaL_reg allua_filesystem_methods[] = {
   {"make_directory", allua_make_directory},
   {"filename_exists", allua_filename_exists},
   {"remove_filename", allua_remove_filename},
   {"change_directory", allua_change_directory},
   {0, 0}
};

/* Register
 * */
int allua_register_filesystem(lua_State * L)
{
   lua_newtable(L);
   luaL_register(L, NULL, allua_filesystem_methods);    /* create methods table,
                                                           add it to the globals */

   lua_setfield(L, -2, FILESYSTEM_STRING);
   return 0;                    /* return methods on the stack */
}
