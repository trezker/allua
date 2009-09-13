#include "allua/bitmap.h"
#include "allua/color.h"
#include "allua/allua.h"
#include <stdio.h>
#include <allegro5/allegro_image.h>

#define BITMAP_STRING "bitmap"

/* Common handlers
 * */
/*static ALLUA_bitmap toBitmap (lua_State *L, int index)//, int *gc_allowed)
{
  struct ALLUA_bitmap_s *pi = (struct ALLUA_bitmap_s*)lua_touserdata(L, index);
  if (pi == NULL) luaL_typerror(L, index, BITMAP_STRING);
//  if(gc_allowed)
//  	*gc_allowed = pi->gc_allowed;
  return pi->bitmap;
}
*/
ALLUA_bitmap allua_check_bitmap (lua_State *L, int index)//, int *gc_allowed)
{
  struct ALLUA_bitmap_s *pi;
  ALLUA_bitmap im;
  luaL_checktype(L, index, LUA_TUSERDATA);
  pi = (struct ALLUA_bitmap_s*)luaL_checkudata(L, index, BITMAP_STRING);
  if (pi == NULL)
  	luaL_typerror(L, index, BITMAP_STRING);
  im = pi->bitmap;
  if (!im)
    luaL_error(L, "null bitmap");
  return im;
}

struct ALLUA_bitmap_s *allua_pushBitmap (lua_State *L, ALLUA_bitmap im, int gc_allowed)
{
  struct ALLUA_bitmap_s *pi = (struct ALLUA_bitmap_s *)lua_newuserdata(L, sizeof(struct ALLUA_bitmap_s));
  pi->bitmap = im;
  pi->gc_allowed = gc_allowed;
  luaL_getmetatable(L, BITMAP_STRING);
  lua_setmetatable(L, -2);
  return pi;
}

/* Constructor and methods
 * */

static int allua_Bitmap_init_image_addon (lua_State *L)
{
	lua_pushboolean(L, al_init_image_addon());
	return 1;
}

static int allua_Bitmap_clone (lua_State *L)
{
  ALLUA_bitmap bitmap = allua_check_bitmap(L, 1);
  allua_pushBitmap(L, al_clone_bitmap(bitmap), true);
  return 1;
}

static int allua_Bitmap_create (lua_State *L)
{
  int w = luaL_checkint(L, 1);
  int h = luaL_checkint(L, 2);

  allua_pushBitmap(L, al_create_bitmap(w, h), true);

  return 1;
}

static int allua_Bitmap_create_sub (lua_State *L)
{
  ALLUA_bitmap parent = allua_check_bitmap(L, 1);
  int x = luaL_checkint(L, 2);
  int y = luaL_checkint(L, 3);
  int w = luaL_checkint(L, 4);
  int h = luaL_checkint(L, 5);
  ALLUA_bitmap child = al_create_sub_bitmap(parent, x, y, w, h);
  if(child)
    allua_pushBitmap(L, child, true);
  else
    lua_pushnil(L);

  return 1;
}

static int allua_Bitmap_get_new_flags (lua_State *L)
{
  lua_pushinteger(L, al_get_new_bitmap_flags());
  return 1;
}

static int allua_Bitmap_set_new_flags (lua_State *L)
{
  int flags = luaL_checkint(L, 1);
  al_set_new_bitmap_flags(flags);
  return 0;
}

static int allua_Bitmap_get_new_format (lua_State *L)
{
  lua_pushinteger(L, al_get_new_bitmap_format());
  return 1;
}

static int allua_Bitmap_set_new_format (lua_State *L)
{
  int format = luaL_checkint(L, 1);
  al_set_new_bitmap_format(format);
  return 0;
}

static int allua_Bitmap_load (lua_State *L)
{
  const char *filename = luaL_checkstring(L, 1);
  allua_pushBitmap(L, al_load_bitmap(filename), true);
  return 1;
}

static int allua_Bitmap_get_flags (lua_State *L)
{
  ALLUA_bitmap bitmap = allua_check_bitmap(L, 1);
  lua_pushinteger(L, al_get_bitmap_flags(bitmap));
  return 1;
}

static int allua_Bitmap_get_format (lua_State *L)
{
  ALLUA_bitmap bitmap = allua_check_bitmap(L, 1);
  lua_pushinteger(L, al_get_bitmap_format(bitmap));
  return 1;
}

static int allua_Bitmap_get_width (lua_State *L)
{
  ALLUA_bitmap bitmap = allua_check_bitmap(L, 1);

  lua_pushinteger(L, al_get_bitmap_width(bitmap));
  return 1;
}

static int allua_Bitmap_get_height (lua_State *L)
{
  ALLUA_bitmap bitmap = allua_check_bitmap(L, 1);

  lua_pushinteger(L, al_get_bitmap_height(bitmap));
  return 1;
}

static int allua_Bitmap_get_pixel (lua_State *L)
{
  ALLUA_bitmap bitmap = allua_check_bitmap(L, 1);
  float x = luaL_checknumber(L, 2);
  float y = luaL_checknumber(L, 3);
  allua_pushColor(L, al_get_pixel(bitmap, x, y));
  return 1;
}

static int allua_Bitmap_is_locked (lua_State *L)
{
  ALLUA_bitmap bitmap = allua_check_bitmap(L, 1);
  lua_pushboolean(L, al_is_bitmap_locked(bitmap));
  return 1;
}

static int allua_Bitmap_is_compatible (lua_State *L)
{
  ALLUA_bitmap bitmap = allua_check_bitmap(L, 1);
  lua_pushboolean(L, al_is_compatible_bitmap(bitmap));
  return 1;
}

static int allua_Bitmap_is_sub (lua_State *L)
{
  ALLUA_bitmap bitmap = allua_check_bitmap(L, 1);
  lua_pushboolean(L, al_is_sub_bitmap(bitmap));
  return 1;
}

static int allua_Bitmap_clear_to_color (lua_State *L)
{
	ALLUA_color color = allua_check_color(L, 1);
	al_clear_to_color(color);
	return 0;
}

static int allua_Bitmap_draw (lua_State *L)
{
  ALLUA_bitmap bitmap = allua_check_bitmap(L, 1);
  float dx = luaL_checknumber(L, 2);
  float dy = luaL_checknumber(L, 3);
  int flags = luaL_checkint(L, 4);

  al_draw_bitmap(bitmap, dx, dy, flags);
  return 0;
}

static int allua_Bitmap_draw_region (lua_State *L)
{
  ALLUA_bitmap bitmap = allua_check_bitmap(L, 1);
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

static int allua_Bitmap_draw_rotated (lua_State *L)
{
  ALLUA_bitmap bitmap = allua_check_bitmap(L, 1);
  float cx = luaL_checknumber(L, 2);
  float cy = luaL_checknumber(L, 3);
  float dx = luaL_checknumber(L, 4);
  float dy = luaL_checknumber(L, 5);
  float angle = luaL_checknumber(L, 6);
  int flags = luaL_checkint(L, 7);

  al_draw_rotated_bitmap(bitmap, cx, cy, dx, dy, angle, flags);
  return 0;
}

static int allua_Bitmap_draw_rotated_scaled (lua_State *L)
{
  ALLUA_bitmap bitmap = allua_check_bitmap(L, 1);
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

static int allua_Bitmap_draw_scaled (lua_State *L)
{
  ALLUA_bitmap bitmap = allua_check_bitmap(L, 1);
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

static int allua_Bitmap_get_target (lua_State *L)
{
  allua_pushBitmap(L, al_get_target_bitmap(), false);
  return 1;
}

static int allua_Bitmap_set_target (lua_State *L)
{
  ALLUA_bitmap bitmap = allua_check_bitmap(L, 1);
  al_set_target_bitmap(bitmap);
  return 0;
}

static int allua_Bitmap_get_clipping_rectangle (lua_State *L)
{
  int x;
  int y;
  int w;
  int h;
  al_get_clipping_rectangle(&x, &y, &w, &h);
  lua_pushinteger(L, x);
  lua_pushinteger(L, y);
  lua_pushinteger(L, w);
  lua_pushinteger(L, h);
  return 4;
}

static int allua_Bitmap_set_clipping_rectangle (lua_State *L)
{
	int x = luaL_checknumber(L, 1);
	int y = luaL_checknumber(L, 2);
	int w = luaL_checknumber(L, 3);
	int h = luaL_checknumber(L, 4);
	al_set_clipping_rectangle(x, y, w, h);
	return 0;
}

static int allua_Bitmap_convert_mask_to_alpha(lua_State *L)
{
	ALLUA_bitmap bitmap = allua_check_bitmap(L, 1);
	ALLUA_color color = allua_check_color(L, 2);
	al_convert_mask_to_alpha(bitmap, color);
	return 0;
}

static const luaL_reg allua_Bitmap_methods[] = {
  {"init_image_addon",           allua_Bitmap_init_image_addon},
  {"clone",           allua_Bitmap_clone},
  {"create",           allua_Bitmap_create},
  {"create_sub",           allua_Bitmap_create_sub},
  {"get_new_flags",           allua_Bitmap_get_new_flags},
  {"set_new_flags",           allua_Bitmap_set_new_flags},
  {"get_new_format",           allua_Bitmap_get_new_format},
  {"set_new_format",           allua_Bitmap_set_new_format},
  {"load",           allua_Bitmap_load},
  {"get_flags",           allua_Bitmap_get_flags},
  {"get_format",           allua_Bitmap_get_format},
  {"get_width",           allua_Bitmap_get_width},
  {"get_height",           allua_Bitmap_get_height},
  {"get_pixel",           allua_Bitmap_get_pixel},
  {"is_locked",           allua_Bitmap_is_locked},
  {"is_compatible",           allua_Bitmap_is_compatible},
  {"is_sub",           allua_Bitmap_is_sub},
  {"clear_to_color",           allua_Bitmap_clear_to_color},
  {"draw",           allua_Bitmap_draw},
  {"draw_region",           allua_Bitmap_draw_region},
  {"draw_rotated",           allua_Bitmap_draw_rotated},
  {"draw_rotated_scaled",           allua_Bitmap_draw_rotated_scaled},
  {"draw_scaled",           allua_Bitmap_draw_scaled},
  {"get_target",           allua_Bitmap_get_target},
  {"set_target",           allua_Bitmap_set_target},
  {"get_clipping_rectangle",           allua_Bitmap_get_clipping_rectangle},
  {"set_clipping_rectangle",           allua_Bitmap_set_clipping_rectangle},
  {"convert_mask_to_alpha",           allua_Bitmap_convert_mask_to_alpha},
  {0,0}
};

/* GC and meta
 * */
static int allua_Bitmap_gc (lua_State *L)
{
  struct ALLUA_bitmap_s *pi = (struct ALLUA_bitmap_s*)lua_touserdata(L, 1);
  if(pi->gc_allowed)
  {
	  ALLUA_bitmap im = pi->bitmap;
	  printf("goodbye bitmap (%p)\n", im);
	  if (im) al_destroy_bitmap(im);
  }
  return 0;
}

static int allua_Bitmap_tostring (lua_State *L)
{
  lua_pushfstring(L, "bitmap: %p", lua_touserdata(L, 1));
  return 1;
}

static const luaL_reg allua_Bitmap_meta[] = {
  {"__gc",       allua_Bitmap_gc},
  {"__tostring", allua_Bitmap_tostring},
  {0, 0}
};

/* Other attributes
 * */
void allua_Bitmap_set_attributes(lua_State *L)
{
	lua_pushinteger(L, ALLEGRO_MEMORY_BITMAP);
	lua_setfield(L, -2, "MEMORY_BITMAP");
	lua_pushinteger(L, ALLEGRO_KEEP_BITMAP_FORMAT);
	lua_setfield(L, -2, "KEEP_BITMAP_FORMAT");
	lua_pushinteger(L, ALLEGRO_FORCE_LOCKING);
	lua_setfield(L, -2, "FORCE_LOCKING");
	lua_pushinteger(L, ALLEGRO_NO_PRESERVE_TEXTURE);
	lua_setfield(L, -2, "NO_PRESERVE_TEXTURE");

	lua_pushinteger(L, ALLEGRO_FLIP_HORIZONTAL);
	lua_setfield(L, -2, "FLIP_HORIZONTAL");
	lua_pushinteger(L, ALLEGRO_FLIP_VERTICAL);
	lua_setfield(L, -2, "FLIP_VERTICAL");
}

/* Register
 * */
int allua_register_bitmap (lua_State *L)
{
  lua_newtable (L);
  luaL_register(L, NULL, allua_Bitmap_methods);  /* create methods table,
                                                add it to the globals */

	allua_Bitmap_set_attributes(L);

  luaL_newmetatable(L, BITMAP_STRING);        /* create metatable for Image,
                                         add it to the Lua registry */
  luaL_register(L, 0, allua_Bitmap_meta);  /* fill metatable */
  lua_pushliteral(L, "__index");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* metatable.__index = methods */
  lua_pushliteral(L, "__metatable");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* hide metatable:
                                         metatable.__metatable = methods */
  lua_pop(L, 1);                      /* drop metatable */

  lua_setfield(L, -2, BITMAP_STRING);

  return 0;                           /* return methods on the stack */
}
