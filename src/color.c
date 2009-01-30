#include "color.h"
#include <stdio.h>

#define COLOR "Color"

/* Common handlers
 * */
static AL_Color toColor (lua_State *L, int index)
{
  AL_Color *pi = (AL_Color*)lua_touserdata(L, index);
  if (pi == NULL) luaL_typerror(L, index, COLOR);
  return *pi;
}

AL_Color al_lua_check_color (lua_State *L, int index)
{
  AL_Color *pi, im;
  luaL_checktype(L, index, LUA_TUSERDATA);
  pi = (AL_Color*)luaL_checkudata(L, index, COLOR);
  if (pi == NULL)
  	luaL_typerror(L, index, COLOR);
  im = *pi;
  return im;
}

static AL_Color *pushColor (lua_State *L, AL_Color im)
{
  AL_Color *pi = (AL_Color *)lua_newuserdata(L, sizeof(AL_Color));
  *pi = im;
  luaL_getmetatable(L, COLOR);
  lua_setmetatable(L, -2);
  return pi;
}

/* Constructor and methods
 * */
static int al_lua_map_rgba(lua_State *L)
{
	int r = luaL_checkint(L, 1);
	int g = luaL_checkint(L, 2);
	int b = luaL_checkint(L, 3);
	int a = luaL_checkint(L, 4);
	pushColor(L, al_map_rgba(r, g, b, a));
	return 1;
}

static int al_lua_put_pixel(lua_State *L)
{
	int x = luaL_checkint(L, 1);
	int y = luaL_checkint(L, 2);
	AL_Color color = al_lua_check_color(L, 3);
	al_put_pixel(x, y, color);
	return 0;
}

static const luaL_reg Color_methods[] = {
  {"map_rgba",           al_lua_map_rgba},
  {"put_pixel",           al_lua_put_pixel},
  {0,0}
};

/* GC and meta
 * */
static int Color_tostring (lua_State *L)
{
  lua_pushfstring(L, "Color: %p", lua_touserdata(L, 1));
  return 1;
}

static const luaL_reg Color_meta[] = {
  {"__tostring", Color_tostring},
  {0, 0}
};

/* Register
 * */
int al_lua_register_color (lua_State *L)
{
  luaL_register(L, COLOR, Color_methods);  /* create methods table,
                                                add it to the globals */

  luaL_newmetatable(L, COLOR);        /* create metatable for Image,
                                         add it to the Lua registry */
  luaL_register(L, 0, Color_meta);  /* fill metatable */
  lua_pushliteral(L, "__index");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* metatable.__index = methods */
  lua_pushliteral(L, "__metatable");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* hide metatable:
                                         metatable.__metatable = methods */
  lua_pop(L, 1);                      /* drop metatable */

  return 1;                           /* return methods on the stack */
}
