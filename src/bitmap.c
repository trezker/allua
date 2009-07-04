#include "allua/bitmap.h"
#include "allua/color.h"
#include "allua/al_lua.h"
#include <stdio.h>
#include <allegro5/a5_iio.h>

#define BITMAP "bitmap"

/* Common handlers
 * */
/*static AL_bitmap toBitmap (lua_State *L, int index)//, int *gc_allowed)
{
  struct AL_bitmap_s *pi = (struct AL_bitmap_s*)lua_touserdata(L, index);
  if (pi == NULL) luaL_typerror(L, index, BITMAP);
//  if(gc_allowed)
//  	*gc_allowed = pi->gc_allowed;
  return pi->bitmap;
}
*/
AL_bitmap al_lua_check_bitmap (lua_State *L, int index)//, int *gc_allowed)
{
  struct AL_bitmap_s *pi;
  AL_bitmap im;
  luaL_checktype(L, index, LUA_TUSERDATA);
  pi = (struct AL_bitmap_s*)luaL_checkudata(L, index, BITMAP);
  if (pi == NULL)
  	luaL_typerror(L, index, BITMAP);
  im = pi->bitmap;
//  if(gc_allowed)
//  	*gc_allowed = pi->gc_allowed;
  if (!im)
    luaL_error(L, "null bitmap");
  return im;
}

struct AL_bitmap_s *pushBitmap (lua_State *L, AL_bitmap im, int gc_allowed)
{
  struct AL_bitmap_s *pi = (struct AL_bitmap_s *)lua_newuserdata(L, sizeof(struct AL_bitmap_s));
  pi->bitmap = im;
  pi->gc_allowed = gc_allowed;
  luaL_getmetatable(L, BITMAP);
  lua_setmetatable(L, -2);
  return pi;
}

/* Constructor and methods
 * */
static int Bitmap_clone (lua_State *L)
{
  AL_bitmap bitmap = al_lua_check_bitmap(L, 1);
  pushBitmap(L, al_clone_bitmap(bitmap), true);
  return 1;
}

static int Bitmap_create (lua_State *L)
{
  int w = luaL_checkint(L, 1);
  int h = luaL_checkint(L, 2);

  pushBitmap(L, al_create_bitmap(w, h), true);

  return 1;
}

static int Bitmap_create_sub (lua_State *L)
{
  AL_bitmap parent = al_lua_check_bitmap(L, 1);
  int x = luaL_checkint(L, 2);
  int y = luaL_checkint(L, 3);
  int w = luaL_checkint(L, 4);
  int h = luaL_checkint(L, 5);
  AL_bitmap child = al_create_sub_bitmap(parent, x, y, w, h);
  if(child)
    pushBitmap(L, child, true);
  else
    lua_pushnil(L);

  return 1;
}

static int Bitmap_get_new_flags (lua_State *L)
{
  lua_pushinteger(L, al_get_new_bitmap_flags());
  return 1;
}

static int Bitmap_set_new_flags (lua_State *L)
{
  int flags = luaL_checkint(L, 1);
  al_set_new_bitmap_flags(flags);
  return 0;
}

static int Bitmap_get_new_format (lua_State *L)
{
  lua_pushinteger(L, al_get_new_bitmap_format());
  return 1;
}

static int Bitmap_set_new_format (lua_State *L)
{
  int format = luaL_checkint(L, 1);
  al_set_new_bitmap_format(format);
  return 0;
}

static int Bitmap_load (lua_State *L)
{
  const char *filename = luaL_checkstring(L, 1);
  pushBitmap(L, al_load_bitmap(filename), true);
  return 1;
}

static int Bitmap_get_flags (lua_State *L)
{
  AL_bitmap bitmap = al_lua_check_bitmap(L, 1);
  lua_pushinteger(L, al_get_bitmap_flags(bitmap));
  return 1;
}

static int Bitmap_get_format (lua_State *L)
{
  AL_bitmap bitmap = al_lua_check_bitmap(L, 1);
  lua_pushinteger(L, al_get_bitmap_format(bitmap));
  return 1;
}

static int Bitmap_get_width (lua_State *L)
{
  AL_bitmap bitmap = al_lua_check_bitmap(L, 1);

  lua_pushinteger(L, al_get_bitmap_width(bitmap));
  return 1;
}

static int Bitmap_get_height (lua_State *L)
{
  AL_bitmap bitmap = al_lua_check_bitmap(L, 1);

  lua_pushinteger(L, al_get_bitmap_height(bitmap));
  return 1;
}

static int Bitmap_get_pixel (lua_State *L)
{
  AL_bitmap bitmap = al_lua_check_bitmap(L, 1);
  float x = luaL_checknumber(L, 2);
  float y = luaL_checknumber(L, 3);
  pushColor(L, al_get_pixel(bitmap, x, y));
  return 1;
}

static int Bitmap_is_locked (lua_State *L)
{
  AL_bitmap bitmap = al_lua_check_bitmap(L, 1);
  lua_pushboolean(L, al_is_bitmap_locked(bitmap));
  return 1;
}

static int Bitmap_is_compatible (lua_State *L)
{
  AL_bitmap bitmap = al_lua_check_bitmap(L, 1);
  lua_pushboolean(L, al_is_compatible_bitmap(bitmap));
  return 1;
}

static int Bitmap_is_sub (lua_State *L)
{
  AL_bitmap bitmap = al_lua_check_bitmap(L, 1);
  lua_pushboolean(L, al_is_sub_bitmap(bitmap));
  return 1;
}

static int Bitmap_clear_to_color (lua_State *L)
{
	AL_color color = al_lua_check_color(L, 1);
	al_clear_to_color(color);
	return 0;
}

static int Bitmap_draw (lua_State *L)
{
  AL_bitmap bitmap = al_lua_check_bitmap(L, 1);
  float dx = luaL_checknumber(L, 2);
  float dy = luaL_checknumber(L, 3);
  int flags = luaL_checkint(L, 4);

  al_draw_bitmap(bitmap, dx, dy, flags);
  return 0;
}

static int Bitmap_draw_region (lua_State *L)
{
  AL_bitmap bitmap = al_lua_check_bitmap(L, 1);
  float sx = luaL_checknumber(L, 2);
  float sy = luaL_checknumber(L, 3);
  float sw = luaL_checknumber(L, 4);
  float sh = luaL_checknumber(L, 5);
  float dx = luaL_checknumber(L, 6);
  float dy = luaL_checknumber(L, 7);
  int flags = luaL_checkint(L, 8);

  al_draw_bitmap_region(bitmap, sx, sy, sw, sh, dx, dy, flags);
  return 0;
}

static int Bitmap_draw_rotated (lua_State *L)
{
  AL_bitmap bitmap = al_lua_check_bitmap(L, 1);
  float cx = luaL_checknumber(L, 2);
  float cy = luaL_checknumber(L, 3);
  float dx = luaL_checknumber(L, 4);
  float dy = luaL_checknumber(L, 5);
  float angle = luaL_checknumber(L, 6);
  int flags = luaL_checkint(L, 7);

  al_draw_rotated_bitmap(bitmap, cx, cy, dx, dy, angle, flags);
  return 0;
}

static int Bitmap_draw_rotated_scaled (lua_State *L)
{
  AL_bitmap bitmap = al_lua_check_bitmap(L, 1);
  float cx = luaL_checknumber(L, 2);
  float cy = luaL_checknumber(L, 3);
  float dx = luaL_checknumber(L, 4);
  float dy = luaL_checknumber(L, 5);
  float scalex = luaL_checknumber(L, 6);
  float scaley = luaL_checknumber(L, 7);
  float angle = luaL_checknumber(L, 8);
  int flags = luaL_checkint(L, 9);

  al_draw_rotated_scaled_bitmap(bitmap, cx, cy, dx, dy, scalex, scaley, angle, flags);
  return 0;
}

static int Bitmap_draw_scaled (lua_State *L)
{
  AL_bitmap bitmap = al_lua_check_bitmap(L, 1);
  float sx = luaL_checknumber(L, 2);
  float sy = luaL_checknumber(L, 3);
  float sw = luaL_checknumber(L, 4);
  float sh = luaL_checknumber(L, 5);
  float dx = luaL_checknumber(L, 6);
  float dy = luaL_checknumber(L, 7);
  float dw = luaL_checknumber(L, 8);
  float dh = luaL_checknumber(L, 9);
  int flags = luaL_checkint(L, 10);

  al_draw_scaled_bitmap(bitmap, sx, sy, sw, sh, dx, dy, dw, dh, flags);
  return 0;
}

static const luaL_reg Bitmap_methods[] = {
  {"clone",           Bitmap_clone},
  {"create",           Bitmap_create},
  {"create_sub",           Bitmap_create_sub},
  {"get_new_flags",           Bitmap_get_new_flags},
  {"set_new_flags",           Bitmap_set_new_flags},
  {"get_new_format",           Bitmap_get_new_format},
  {"set_new_format",           Bitmap_set_new_format},
  {"load",           Bitmap_load},
  {"get_flags",           Bitmap_get_flags},
  {"get_format",           Bitmap_get_format},
  {"get_width",           Bitmap_get_width},
  {"get_height",           Bitmap_get_height},
  {"get_pixel",           Bitmap_get_pixel},
  {"is_locked",           Bitmap_is_locked},
  {"is_compatible",           Bitmap_is_compatible},
  {"is_sub",           Bitmap_is_sub},
  {"clear_to_color",           Bitmap_clear_to_color},
  {"draw",           Bitmap_draw},
  {"draw_region",           Bitmap_draw_region},
  {"draw_rotated",           Bitmap_draw_rotated},
  {"draw_rotated_scaled",           Bitmap_draw_rotated_scaled},
  {"draw_scaled",           Bitmap_draw_scaled},
  {0,0}
};

/* GC and meta
 * */
static int Bitmap_gc (lua_State *L)
{
  struct AL_bitmap_s *pi = (struct AL_bitmap_s*)lua_touserdata(L, 1);
  if(pi->gc_allowed)
  {
	  AL_bitmap im = pi->bitmap;
	  printf("goodbye bitmap (%p)\n", im);
	  if (im) al_destroy_bitmap(im);
  }
  return 0;
}

static int Bitmap_tostring (lua_State *L)
{
  lua_pushfstring(L, "bitmap: %p", lua_touserdata(L, 1));
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
	lua_pushinteger(L, ALLEGRO_MEMORY_BITMAP);
	lua_setfield(L, -2, "MEMORY_BITMAP");
	lua_pushinteger(L, ALLEGRO_KEEP_BITMAP_FORMAT);
	lua_setfield(L, -2, "KEEP_BITMAP_FORMAT");
	lua_pushinteger(L, ALLEGRO_FORCE_LOCKING);
	lua_setfield(L, -2, "FORCE_LOCKING");
	lua_pushinteger(L, ALLEGRO_NO_PRESERVE_TEXTURE);
	lua_setfield(L, -2, "NO_PRESERVE_TEXTURE");
}

/* Register
 * */
int al_lua_register_bitmap (lua_State *L)
{
  lua_newtable (L);
  luaL_register(L, NULL, Bitmap_methods);  /* create methods table,
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

  lua_setfield(L, -2, BITMAP);

  return 0;                           /* return methods on the stack */
}
