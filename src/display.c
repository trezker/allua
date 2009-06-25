#include "allua/display.h"
#include "allua/al_lua.h"
#include "allua/color.h"
#include "allua/event_queue.h"
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
/*
static AL_Display *pushDisplay (lua_State *L, AL_Display im)
{
  AL_Display *pi = (AL_Display *)lua_newuserdata(L, sizeof(AL_Display));
  *pi = im;
  luaL_getmetatable(L, DISPLAY);
  lua_setmetatable(L, -2);
  return pi;
}
*/
static AL_Display *pushDisplay (lua_State *L, AL_Display im)
{
	lua_getfield (L, LUA_REGISTRYINDEX, "allegro5udatamap");
    lua_pushlightuserdata(L, (void *)im);  /* push address */
    lua_gettable(L, -2);  /* retrieve value */

	AL_Display *pi;
	if(!lua_isnil (L, -1))
	{
		pi = lua_touserdata (L, -1);
		printf("Retrieved existing display udata \n");
	}
	else
	{
		lua_pop(L, 1); //Pop the nil
		printf("Creating new display udata \n");
		/* Create new userdata */
		lua_pushlightuserdata(L, (void *)im); //Key
		pi = (AL_Display *)lua_newuserdata(L, sizeof(AL_Display)); //value
		*pi = im;
		luaL_getmetatable(L, DISPLAY);
		lua_setmetatable(L, -2);
		lua_settable(L, -3);

		lua_pushlightuserdata(L, (void *)im);  /* push address */
		lua_gettable(L, -2);  /* retrieve value */
	}
	lua_remove (L, -2);
	return pi;
}

/* Constructor and methods
 * */
static int Display_create (lua_State *L)
{
  int x = luaL_checkint(L, 1);
  int y = luaL_checkint(L, 2);
  int flags = lua_tointeger (L, 3);

  al_set_new_display_flags(flags);
  pushDisplay(L, al_create_display(x, y));

  return 1;
}

static int Display_flip (lua_State *L)
{
	al_flip_display();
	return 0;
}

static int Display_set_current (lua_State *L)
{
	AL_Display display = al_lua_check_display(L, 1);
	lua_pushboolean(L, al_set_current_display(display));
	return 1;
}

static int Display_acknowledge_resize (lua_State *L)
{
	AL_Display display = al_lua_check_display(L, 1);
	lua_pushboolean(L, al_acknowledge_resize(display));
	return 1;
}

static int Display_clear (lua_State *L)
{
	AL_Color color = al_lua_check_color(L, 1);
	al_clear_to_color(color);
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
  {"create",           Display_create},
  {"flip",           Display_flip},
  {"set_current",           Display_set_current},
  {"acknowledge_resize",           Display_acknowledge_resize},
  {"clear",           Display_clear},
  {"draw_pixel",           al_lua_draw_pixel},
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

/* Event callbacks
 * */
void al_lua_display_event_callback(lua_State *L, ALLEGRO_EVENT *event)
{
	printf("Allegro event source: %p \n",event->display.source);
	pushDisplay(L, event->display.source);
	lua_setfield(L, -2, "source");

	Set_literal("x", event->display.x, -3);
	Set_literal("y", event->display.y, -3);
	Set_literal("width", event->display.width, -3);
	Set_literal("height", event->display.height, -3);
}

/* Other attributes
 * */
void Display_set_attributes(lua_State *L)
{
	Set_literal("EVENT_CLOSE", ALLEGRO_EVENT_DISPLAY_CLOSE, -3);
	Set_literal("EVENT_SWITCH_OUT", ALLEGRO_EVENT_DISPLAY_SWITCH_OUT, -3);
	Set_literal("EVENT_RESIZE", ALLEGRO_EVENT_DISPLAY_RESIZE, -3);

	Set_literal("WINDOWED", ALLEGRO_WINDOWED, -3);
	Set_literal("FULLSCREEN", ALLEGRO_FULLSCREEN, -3);
	Set_literal("RESIZABLE", ALLEGRO_RESIZABLE, -3);
}

/* Register
 * */
int al_lua_register_display (lua_State *L)
{
	al_lua_set_event_callback(ALLEGRO_EVENT_DISPLAY_RESIZE, al_lua_display_event_callback);
	al_lua_set_event_callback(ALLEGRO_EVENT_DISPLAY_CLOSE, al_lua_display_event_callback);

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
