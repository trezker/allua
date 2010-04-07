#include "../include/allua/filesystem.h"
#include <allegro5/allegro.h>
#include <stdio.h>

#define FILESYSTEM_STRING "filesystem"

/* Methods
 * */
static int allua_make_directory(lua_State *L)
{
	const char* path = luaL_checkstring(L, 1);
	lua_pushboolean(L, al_make_directory(path));
	return 1;
}

static const luaL_reg allua_filesystem_methods[] = {
  {"make_directory",           allua_make_directory},
  {0,0}
};

/* Register
 * */
int allua_register_filesystem (lua_State *L)
{
  lua_newtable(L);
  luaL_register(L, NULL, allua_filesystem_methods);  /* create methods table,
                                                add it to the globals */

  lua_setfield(L, -2, FILESYSTEM_STRING);
  return 0;                           /* return methods on the stack */
}
