#include "bitmap.h"
#include "al_lua.h"
#include <stdio.h>
#include <allegro5/a5_iio.h>

#define BITMAP "Bitmap"

/* Common handlers
 * */
static AL_Bitmap toBitmap (lua_State *L, int index)
{
  AL_Bitmap *pi = (AL_Bitmap*)lua_touserdata(L, index);
  if (pi == NULL) luaL_typerror(L, index, BITMAP);
  return *pi;
}

AL_Bitmap al_lua_check_bitmap (lua_State *L, int index)
{
  AL_Bitmap *pi, im;
  luaL_checktype(L, index, LUA_TUSERDATA);
  pi = (AL_Bitmap*)luaL_checkudata(L, index, BITMAP);
  if (pi == NULL)
  	luaL_typerror(L, index, BITMAP);
  im = *pi;
  if (!im)
    luaL_error(L, "null Bitmap");
  return im;
}

static AL_Bitmap *pushBitmap (lua_State *L, AL_Bitmap im)
{
  AL_Bitmap *pi = (AL_Bitmap *)lua_newuserdata(L, sizeof(AL_Bitmap));
  *pi = im;
  luaL_getmetatable(L, BITMAP);
  lua_setmetatable(L, -2);
  return pi;
}

/* Constructor and methods
 * */
static int Bitmap_new (lua_State *L)
{
  int w = luaL_checkint(L, 1);
  int h = luaL_checkint(L, 2);

  pushBitmap(L, al_create_bitmap(w, h));

  return 1;
}

static int Bitmap_load (lua_State *L)
{
  const char *filename = luaL_checkstring(L, 1);
  pushBitmap(L, al_iio_load(filename));
  return 1;
}

static int Bitmap_draw (lua_State *L)
{
  AL_Bitmap bitmap = al_lua_check_bitmap(L, 1);
  float dx = luaL_checknumber(L, 2);
  float dy = luaL_checknumber(L, 3);
  int flags = luaL_checkint(L, 4);

  al_draw_bitmap(bitmap, dx, dy, flags);
  return 1;
}

static const luaL_reg Bitmap_methods[] = {
  {"new",           Bitmap_new},
  {"load",           Bitmap_load},
  {"draw",           Bitmap_draw},
  {0,0}
};

/* GC and meta
 * */
static int Bitmap_gc (lua_State *L)
{
  AL_Bitmap im = toBitmap(L, 1);
  printf("goodbye Bitmap (%p)\n", im);
  if (im) al_destroy_bitmap(im);
  return 0;
}

static int Bitmap_tostring (lua_State *L)
{
  lua_pushfstring(L, "Bitmap: %p", lua_touserdata(L, 1));
  return 1;
}

static const luaL_reg Bitmap_meta[] = {
  {"__gc",       Bitmap_gc},
  {"__tostring", Bitmap_tostring},
  {0, 0}
};

/* Other attributes
 * */
void Bitmap_set_attributes(lua_State *L)
{
}

/* Register
 * */
int al_lua_register_bitmap (lua_State *L)
{
  luaL_register(L, BITMAP, Bitmap_methods);  /* create methods table,
                                                add it to the globals */

	Bitmap_set_attributes(L);

  luaL_newmetatable(L, BITMAP);        /* create metatable for Image,
                                         add it to the Lua registry */
  luaL_register(L, 0, Bitmap_meta);  /* fill metatable */
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
