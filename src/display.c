#include "display.h"
#include "al_lua.h"
#include "color.h"
#include <stdio.h>

#define DISPLAY "Display"

/* Common handlers
 * */
static AL_Display toDisplay (lua_State *L, int index)
{
  AL_Display *pi = (AL_Display*)lua_touserdata(L, index);
  if (pi == NULL) luaL_typerror(L, index, DISPLAY);
  return *pi;
}

AL_Display al_lua_check_display (lua_State *L, int index)
{
  AL_Display *pi, im;
  luaL_checktype(L, index, LUA_TUSERDATA);
  pi = (AL_Display*)luaL_checkudata(L, index, DISPLAY);
  if (pi == NULL)
  	luaL_typerror(L, index, DISPLAY);
  im = *pi;
  if (!im)
    luaL_error(L, "null Display");
  return im;
}

static AL_Display *pushDisplay (lua_State *L, AL_Display im)
{
  AL_Display *pi = (AL_Display *)lua_newuserdata(L, sizeof(AL_Display));
  *pi = im;
  luaL_getmetatable(L, DISPLAY);
  lua_setmetatable(L, -2);
  return pi;
}

/* Constructor and methods
 * */
static int Display_new (lua_State *L)
{
  int x = luaL_checkint(L, 1);
  int y = luaL_checkint(L, 2);
  int flags = lua_toboolean (L, 3);

  al_set_new_display_flags(flags);
  pushDisplay(L, al_create_display(x, y));

  return 1;
}

static int Display_flip (lua_State *L)
{
	al_flip_display();
	return 0;
}

static int Display_clear (lua_State *L)
{
	AL_Color color = al_lua_check_color(L, 1);
	al_clear(color);
	return 0;
}

static int al_lua_draw_pixel(lua_State *L)
{
	int x = luaL_checkint(L, 1);
	int y = luaL_checkint(L, 2);
	AL_Color color = al_lua_check_color(L, 3);
	al_draw_pixel(x, y, color);
	return 0;
}
static int al_lua_draw_line(lua_State *L)
{
	int fx = luaL_checkint(L, 1);
	int fy = luaL_checkint(L, 2);
	int tx = luaL_checkint(L, 3);
	int ty = luaL_checkint(L, 4);
	AL_Color color = al_lua_check_color(L, 5);
	al_draw_line(fx, fy, tx, ty, color);
	return 0;
}
static int al_lua_draw_rectangle(lua_State *L)
{
	int tlx = luaL_checkint(L, 1);
	int tly = luaL_checkint(L, 2);
	int brx = luaL_checkint(L, 3);
	int bry = luaL_checkint(L, 4);
	AL_Color color = al_lua_check_color(L, 5);
	int flags = luaL_checkint(L, 6);
	al_draw_rectangle(tlx, tly, brx, bry, color, flags);
	return 0;
}

static int al_lua_display_height(lua_State *L)
{
	lua_pushinteger(L, al_get_display_height());
	return 1;
}

static int al_lua_display_width(lua_State *L)
{
	lua_pushinteger(L, al_get_display_width());
	return 1;
}

static const luaL_reg Display_methods[] = {
  {"new",           Display_new},
  {"flip",           Display_flip},
  {"clear",           Display_clear},
  {"draw_pixel",           al_lua_draw_pixel},
  {"draw_line",           al_lua_draw_line},
  {"draw_rectangle",           al_lua_draw_rectangle},
  {"height",           al_lua_display_height},
  {"width",           al_lua_display_width},
  {0,0}
};

/* GC and meta
 * */
static int Display_gc (lua_State *L)
{
  AL_Display im = toDisplay(L, 1);
  printf("goodbye Display (%p)\n", im);
  if (im) al_destroy_display(im);
  return 0;
}

static int Display_tostring (lua_State *L)
{
  lua_pushfstring(L, "Display: %p", lua_touserdata(L, 1));
  return 1;
}

static const luaL_reg Display_meta[] = {
  {"__gc",       Display_gc},
  {"__tostring", Display_tostring},
  {0, 0}
};

/* Other attributes
 * */
void Display_set_attributes(lua_State *L)
{
	Set_literal("EVENT_CLOSE", ALLEGRO_EVENT_DISPLAY_CLOSE, -3);
	Set_literal("EVENT_SWITCH_OUT", ALLEGRO_EVENT_DISPLAY_SWITCH_OUT, -3);
	Set_literal("WINDOWED", ALLEGRO_WINDOWED, -3);
	Set_literal("FULLSCREEN", ALLEGRO_FULLSCREEN, -3);
}

/* Register
 * */
int al_lua_register_display (lua_State *L)
{
  lua_newtable(L);
  luaL_register(L, NULL, Display_methods);  /* create methods table,
                                                add it to the globals */

	Display_set_attributes(L);

  luaL_newmetatable(L, DISPLAY);        /* create metatable for Image,
                                         add it to the Lua registry */
  luaL_register(L, 0, Display_meta);  /* fill metatable */
  lua_pushliteral(L, "__index");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* metatable.__index = methods */
  lua_pushliteral(L, "__metatable");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* hide metatable:
                                         metatable.__metatable = methods */
  lua_pop(L, 1);                      /* drop metatable */

  lua_setfield(L, -2, DISPLAY);

  return 0;                           /* return methods on the stack */
}
