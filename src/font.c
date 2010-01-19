#include "../include/allua/font.h"
#include "../include/allua/allua.h"
#include <stdio.h>
#include <allegro5/allegro_image.h>

#define FONT_STRING "font"

/* Common handlers
 * */
static ALLUA_font allua_toFont (lua_State *L, int index)
{
  ALLUA_font *pi = (ALLUA_font*)lua_touserdata(L, index);
  if (pi == NULL) luaL_typerror(L, index, FONT_STRING);
  return *pi;
}

ALLUA_font allua_check_font (lua_State *L, int index)
{
  ALLUA_font *pi, im;
  luaL_checktype(L, index, LUA_TUSERDATA);
  pi = (ALLUA_font*)luaL_checkudata(L, index, FONT_STRING);
  if (pi == NULL)
  	luaL_typerror(L, index, FONT_STRING);
  im = *pi;
  if (!im)
    luaL_error(L, "null Font");
  return im;
}

static ALLUA_font *allua_pushFont (lua_State *L, ALLUA_font im)
{
  ALLUA_font *pi = (ALLUA_font *)lua_newuserdata(L, sizeof(ALLUA_font));
  *pi = im;
  luaL_getmetatable(L, FONT_STRING);
  lua_setmetatable(L, -2);
  return pi;
}

/* Constructor and methods
 * */

static int allua_Font_init_addon (lua_State *L)
{
	al_init_font_addon();
	return 0;
}

static int allua_Font_init_ttf_addon (lua_State *L)
{
	lua_pushboolean(L, al_init_ttf_addon());
	return 1;
}

static int allua_Font_load (lua_State *L)
{
	const char* filename = luaL_checkstring(L, 1);
	int size = luaL_checkint(L, 2);
	int flags = luaL_checkint(L, 3);
	ALLUA_font font = al_load_font(filename, size, flags);
	if(font)
		allua_pushFont(L, font);
	else
		lua_pushnil(L);
	return 1;
}

static int allua_Font_load_ttf (lua_State *L)
{
	const char* filename = luaL_checkstring(L, 1);
	int size = luaL_checkint(L, 2);
	int options = luaL_checkint(L, 3);
	ALLUA_font font = al_load_ttf_font(filename, size, options);
	if(font)
		allua_pushFont(L, font);
	else
		lua_pushnil(L);
	return 1;
}

static int allua_Font_load_bitmap (lua_State *L)
{
	const char* filename = luaL_checkstring(L, 1);

	ALLUA_font font = al_load_bitmap_font(filename);
	if(font)
		allua_pushFont(L, font);
	else
		lua_pushnil(L);
	return 1;
}

static int allua_Font_draw_text (lua_State *L)
{
  ALLUA_font font = allua_check_font(L, 1);
  float x = luaL_checknumber(L, 2);
  float y = luaL_checknumber(L, 3);
  int flags = luaL_checkinteger(L, 4);
  const char* text = luaL_checkstring(L, 5);

  al_draw_text(font, x, y, flags, text);
  return 0;
}

static int allua_Font_draw_justified_text (lua_State *L)
{
  ALLUA_font font = allua_check_font(L, 1);
  float x1 = luaL_checknumber(L, 2);
  float x2 = luaL_checknumber(L, 3);
  float y = luaL_checknumber(L, 4);
  float diff = luaL_checknumber(L, 5);
  int flags = luaL_checkinteger(L, 6);
  const char* text = luaL_checkstring(L, 7);

  al_draw_justified_text(font, x1, x2, y, diff, flags, text);
  return 0;
}

static int allua_Font_get_text_dimensions (lua_State *L)
{
	ALLUA_font font = allua_check_font(L, 1);
	const char* text = luaL_checkstring(L, 2);

	int bbx;
	int bby;
	int bbw;
	int bbh;
	int ascent;
	int descent;

	al_get_text_dimensions(font, text, &bbx, &bby, &bbw, &bbh, &ascent, &descent);
	lua_pushinteger(L, bbx);
	lua_pushinteger(L, bby);
	lua_pushinteger(L, bbw);
	lua_pushinteger(L, bbh);
	lua_pushinteger(L, ascent);
	lua_pushinteger(L, descent);
	return 6;
}

static int allua_Font_get_line_height (lua_State *L)
{
	ALLUA_font font = allua_check_font(L, 1);
	lua_pushinteger(L, al_get_font_line_height(font));
	return 1;
}

static int allua_Font_get_text_width (lua_State *L)
{
	ALLUA_font font = allua_check_font(L, 1);
	const char* text = luaL_checkstring(L, 2);
	lua_pushinteger(L, al_get_text_width(font, text));
	return 1;
}

static const luaL_reg allua_Font_methods[] = {
  {"init_addon",           allua_Font_init_addon},
  {"init_ttf_addon",           allua_Font_init_ttf_addon},
  {"load",           allua_Font_load},
  {"load_ttf",           allua_Font_load_ttf},
  {"load_bitmap",           allua_Font_load_bitmap},
  {"draw_text",           allua_Font_draw_text},
  {"draw_justified_text",           allua_Font_draw_justified_text},
  {"get_text_dimensions",           allua_Font_get_text_dimensions},
  {"get_line_height",           allua_Font_get_line_height},
  {"get_text_width",           allua_Font_get_text_width},
  {0,0}
};

/* GC and meta
 * */
static int allua_Font_gc (lua_State *L)
{
  ALLUA_font im = allua_toFont(L, 1);
  printf("goodbye Font (%p)\n", im);
  if (im) al_destroy_font(im);
  return 0;
}

static int allua_Font_tostring (lua_State *L)
{
  lua_pushfstring(L, "font: %p", lua_touserdata(L, 1));
  return 1;
}

static const luaL_reg allua_Font_meta[] = {
  {"__gc",       allua_Font_gc},
  {"__tostring", allua_Font_tostring},
  {0, 0}
};

/* Other attributes
 * */
void allua_Font_set_attributes(lua_State *L)
{
	lua_pushinteger(L, ALLEGRO_ALIGN_LEFT);
	lua_setfield(L, -2, "ALIGN_LEFT");
	lua_pushinteger(L, ALLEGRO_ALIGN_CENTRE);
	lua_setfield(L, -2, "ALIGN_CENTRE");
	lua_pushinteger(L, ALLEGRO_ALIGN_RIGHT);
	lua_setfield(L, -2, "ALIGN_RIGHT");

	lua_pushinteger(L, ALLEGRO_TTF_NO_KERNING);
	lua_setfield(L, -2, "TTF_NO_KERNING");
}

/* Register
 * */
int allua_register_font (lua_State *L)
{
  lua_newtable (L);
  luaL_register(L, NULL, allua_Font_methods);  /* create methods table,
                                                add it to the globals */

	allua_Font_set_attributes(L);

  luaL_newmetatable(L, FONT_STRING);        /* create metatable for Image,
                                         add it to the Lua registry */
  luaL_register(L, 0, allua_Font_meta);  /* fill metatable */
  lua_pushliteral(L, "__index");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* metatable.__index = methods */
  lua_pushliteral(L, "__metatable");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* hide metatable:
                                         metatable.__metatable = methods */
  lua_pop(L, 1);                      /* drop metatable */

  lua_setfield(L, -2, FONT_STRING);
	
  return 0;                           /* return methods on the stack */
}
