#include "allua/color.h"
#include <stdio.h>

#define COLOR_STRING "color"

/* Common handlers
 * */
/*static ALLUA_color toColor (lua_State *L, int index)
{
  ALLUA_color *pi = (ALLUA_color*)lua_touserdata(L, index);
  if (pi == NULL) luaL_typerror(L, index, COLOR_STRING);
  return *pi;
}
*/
ALLUA_color allua_check_color (lua_State *L, int index)
{
  ALLUA_color *pi, im;
  luaL_checktype(L, index, LUA_TUSERDATA);
  pi = (ALLUA_color*)luaL_checkudata(L, index, COLOR_STRING);
  if (pi == NULL)
  	luaL_typerror(L, index, COLOR_STRING);
  im = *pi;
  return im;
}

ALLUA_color *allua_pushColor (lua_State *L, ALLUA_color im)
{
  ALLUA_color *pi = (ALLUA_color *)lua_newuserdata(L, sizeof(ALLUA_color));
  *pi = im;
  luaL_getmetatable(L, COLOR_STRING);
  lua_setmetatable(L, -2);
  return pi;
}

/* Constructor and methods
 * */

/*static void test()
{
	unsigned char r = 1;
	unsigned char g = 2;
	unsigned char b = 3;
	ALLEGRO_COLOR c = al_map_rgb(r, g, b);
	printf("%f %f %f\n", c.r, c.g, c.b);
	unsigned char gr;
	unsigned char gg;
	unsigned char gb;
	al_unmap_rgb(c, &gr, &gg, &gb);
	if(gr != r)
		printf("Wrong red\n");
	if(gg != g)
		printf("Wrong green\n");
	if(gb != b)
		printf("Wrong blue\n");
}
*/
static int allua_map_rgb(lua_State *L)
{
//	test();
	unsigned char r = luaL_checkint(L, 1);
	unsigned char g = luaL_checkint(L, 2);
	unsigned char b = luaL_checkint(L, 3);
	allua_pushColor(L, al_map_rgb(r, g, b));
	return 1;
}

static int allua_map_rgb_f(lua_State *L)
{
	float r = luaL_checknumber(L, 1);
	float g = luaL_checknumber(L, 2);
	float b = luaL_checknumber(L, 3);
	allua_pushColor(L, al_map_rgb_f(r, g, b));
	return 1;
}

static int allua_map_rgba(lua_State *L)
{
	int r = luaL_checkint(L, 1);
	int g = luaL_checkint(L, 2);
	int b = luaL_checkint(L, 3);
	int a = luaL_checkint(L, 4);
	allua_pushColor(L, al_map_rgba(r, g, b, a));
	return 1;
}

static int allua_map_rgba_f(lua_State *L)
{
	float r = luaL_checknumber(L, 1);
	float g = luaL_checknumber(L, 2);
	float b = luaL_checknumber(L, 3);
	float a = luaL_checknumber(L, 4);
	allua_pushColor(L, al_map_rgba_f(r, g, b, a));
	return 1;
}

static int allua_unmap_rgb(lua_State *L)
{
	ALLUA_color c = allua_check_color(L, 1);
	unsigned char r;
	unsigned char g;
	unsigned char b;
	al_unmap_rgb(c, &r, &g, &b);
	
	lua_pushnumber(L, r);
	lua_pushnumber(L, g);
	lua_pushnumber(L, b);
	return 3;
}

static int allua_unmap_rgb_f(lua_State *L)
{
	ALLUA_color c = allua_check_color(L, 1);
	float r;
	float g;
	float b;
	al_unmap_rgb_f(c, &r, &g, &b);
	
	lua_pushnumber(L, r);
	lua_pushnumber(L, g);
	lua_pushnumber(L, b);
	return 3;
}

static int allua_unmap_rgba(lua_State *L)
{
	ALLUA_color c = allua_check_color(L, 1);
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
	al_unmap_rgba(c, &r, &g, &b, &a);
	
	lua_pushnumber(L, r);
	lua_pushnumber(L, g);
	lua_pushnumber(L, b);
	lua_pushnumber(L, a);
	return 4;
}

static int allua_unmap_rgba_f(lua_State *L)
{
	ALLUA_color c = allua_check_color(L, 1);
	float r;
	float g;
	float b;
	float a;
	al_unmap_rgba_f(c, &r, &g, &b, &a);
	
	lua_pushnumber(L, r);
	lua_pushnumber(L, g);
	lua_pushnumber(L, b);
	lua_pushnumber(L, a);
	return 4;
}

static int allua_put_pixel(lua_State *L)
{
	ALLUA_color color = allua_check_color(L, 1);
	int x = luaL_checkint(L, 2);
	int y = luaL_checkint(L, 3);
	al_put_pixel(x, y, color);
	return 0;
}

static int allua_draw_pixel(lua_State *L)
{
	ALLUA_color color = allua_check_color(L, 1);
	int x = luaL_checkint(L, 2);
	int y = luaL_checkint(L, 3);
	al_draw_pixel(x, y, color);
	return 0;
}

static const luaL_reg allua_Color_methods[] = {
  {"map_rgb",           allua_map_rgb},
  {"map_rgb_f",           allua_map_rgb_f},
  {"map_rgba",           allua_map_rgba},
  {"map_rgba_f",           allua_map_rgba_f},
  {"unmap_rgb",           allua_unmap_rgb},
  {"unmap_rgb_f",           allua_unmap_rgb_f},
  {"unmap_rgba",           allua_unmap_rgba},
  {"unmap_rgba_f",           allua_unmap_rgba_f},
  {"put_pixel",           allua_put_pixel},
  {"draw_pixel",           allua_draw_pixel},
  {0,0}
};

/* GC and meta
 * */
static int allua_Color_tostring (lua_State *L)
{
  lua_pushfstring(L, "color: %p", lua_touserdata(L, 1));
  return 1;
}

static const luaL_reg allua_Color_meta[] = {
  {"__tostring", allua_Color_tostring},
  {0, 0}
};

/* Register
 * */
int allua_register_color (lua_State *L)
{
  lua_newtable(L);
  luaL_register(L, NULL, allua_Color_methods);  /* create methods table,
                                                add it to the globals */

  luaL_newmetatable(L, COLOR_STRING);        /* create metatable for Image,
                                         add it to the Lua registry */
  luaL_register(L, 0, allua_Color_meta);  /* fill metatable */
  lua_pushliteral(L, "__index");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* metatable.__index = methods */
  lua_pushliteral(L, "__metatable");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* hide metatable:
                                         metatable.__metatable = methods */
  lua_pop(L, 1);                      /* drop metatable */

  lua_setfield(L, -2, COLOR_STRING);
  return 0;                           /* return methods on the stack */
}
