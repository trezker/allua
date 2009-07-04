#include "allua/font.h"
#include "allua/al_lua.h"
#include <stdio.h>
#include <allegro5/a5_iio.h>

#define FONT "font"

/* Common handlers
 * */
static AL_font toFont (lua_State *L, int index)
{
  AL_font *pi = (AL_font*)lua_touserdata(L, index);
  if (pi == NULL) luaL_typerror(L, index, FONT);
  return *pi;
}

AL_font al_lua_check_font (lua_State *L, int index)
{
  AL_font *pi, im;
  luaL_checktype(L, index, LUA_TUSERDATA);
  pi = (AL_font*)luaL_checkudata(L, index, FONT);
  if (pi == NULL)
  	luaL_typerror(L, index, FONT);
  im = *pi;
  if (!im)
    luaL_error(L, "null Font");
  return im;
}

static AL_font *pushFont (lua_State *L, AL_font im)
{
  AL_font *pi = (AL_font *)lua_newuserdata(L, sizeof(AL_font));
  *pi = im;
  luaL_getmetatable(L, FONT);
  lua_setmetatable(L, -2);
  return pi;
}

/* Constructor and methods
 * */
static int Font_load_ttf (lua_State *L)
{
  const char* filename = luaL_checkstring(L, 1);
  int size = luaL_checkint(L, 2);
  int options = luaL_checkint(L, 3);

  pushFont(L, al_load_ttf_font(filename, size, options));
  return 1;
}

static int Font_load_image (lua_State *L)
{
  const char* filename = luaL_checkstring(L, 1);

  pushFont(L, al_load_bitmap_font(filename));
  return 1;
}

static int Font_textout (lua_State *L)
{
  AL_font font = al_lua_check_font(L, 1);
  float x = luaL_checknumber(L, 2);
  float y = luaL_checknumber(L, 3);
  const char* text = luaL_checkstring(L, 4);
  int chars = luaL_checkint(L, 5);

  int flags = 0;
  al_draw_text(font, x, y, flags, text);
  return 1;
}

static const luaL_reg Font_methods[] = {
  {"load_ttf",           Font_load_ttf},
  {"load_image",           Font_load_image},
  {"textout",           Font_textout},
  {0,0}
};

/* GC and meta
 * */
static int Font_gc (lua_State *L)
{
  AL_font im = toFont(L, 1);
  printf("goodbye Font (%p)\n", im);
  if (im) al_destroy_font(im);
  return 0;
}

static int Font_tostring (lua_State *L)
{
  lua_pushfstring(L, "Font: %p", lua_touserdata(L, 1));
  return 1;
}

static const luaL_reg Font_meta[] = {
  {"__gc",       Font_gc},
  {"__tostring", Font_tostring},
  {0, 0}
};

/* Other attributes
 * */
void Font_set_attributes(lua_State *L)
{
}

/* Register
 * */
int al_lua_register_font (lua_State *L)
{
  lua_newtable (L);
  luaL_register(L, NULL, Font_methods);  /* create methods table,
                                                add it to the globals */

	Font_set_attributes(L);

  luaL_newmetatable(L, FONT);        /* create metatable for Image,
                                         add it to the Lua registry */
  luaL_register(L, 0, Font_meta);  /* fill metatable */
  lua_pushliteral(L, "__index");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* metatable.__index = methods */
  lua_pushliteral(L, "__metatable");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* hide metatable:
                                         metatable.__metatable = methods */
  lua_pop(L, 1);                      /* drop metatable */

  lua_setfield(L, -2, FONT);
	
  return 0;                           /* return methods on the stack */
}
