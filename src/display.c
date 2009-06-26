#include "allua/display.h"
#include "allua/al_lua.h"
#include "allua/color.h"
#include "allua/event_queue.h"

//#include <allegro5/a5_direct3d.h>
#include <allegro5/a5_opengl.h>
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
    lua_pushlightuserdata(L, (void *)im);  // push address 
    lua_gettable(L, -2);  // retrieve value 

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
		// Create new userdata
		lua_pushlightuserdata(L, (void *)im); //Key
		pi = (AL_Display *)lua_newuserdata(L, sizeof(AL_Display)); //value
		*pi = im;
		luaL_getmetatable(L, DISPLAY);
		lua_setmetatable(L, -2);
		lua_settable(L, -3);

		lua_pushlightuserdata(L, (void *)im);  // push address
		lua_gettable(L, -2);  // retrieve value
	}
	lua_remove (L, -2);
	return pi;
}

/* Constructor and methods
 * */
static int Display_create (lua_State *L)
{
  int w = luaL_checkint(L, 1);
  int h = luaL_checkint(L, 2);
  pushDisplay(L, al_create_display(w, h));
  return 1;
}

static int Display_get_num_display_formats(lua_State *L)
{
	lua_pushnumber(L, al_get_num_display_formats());
	return 1;
}

static int Display_get_format_option(lua_State *L)
{
	int i = luaL_checkint(L, 1);
	int option = luaL_checkint(L, 2);
	lua_pushnumber(L, al_get_display_format_option(i, option));
	return 1;
}

static int Display_set_new_format(lua_State *L)
{
	int i = luaL_checkint(L, 1);
	al_set_new_display_format(i);
	return 0;
}

static int Display_get_new_flags(lua_State *L)
{
	lua_pushnumber(L, al_get_new_display_flags());
	return 1;
}

static int Display_get_new_refresh_rate(lua_State *L)
{
	lua_pushnumber(L, al_get_new_display_refresh_rate());
	return 1;
}

static int Display_get_new_window_position(lua_State *L)
{
	int x;
	int y;
	al_get_new_window_position(&x, &y);
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);
	return 2;
}

static int Display_set_new_option(lua_State *L)
{
	int option = luaL_checkint(L, 1);
	int value = luaL_checkint(L, 2);
	int importance = luaL_checkint(L, 3);
	al_set_new_display_option(option, value, importance);
	return 0;
}

static int Display_get_new_option(lua_State *L)
{
	int option = luaL_checkint(L, 1);
	int importance;
	int value = al_get_new_display_option(option, &importance);
	lua_pushnumber(L, value);
	lua_pushnumber(L, importance);
	return 2;
}

static int Display_reset_new_options(lua_State *L)
{
	al_reset_new_display_options();
	return 0;
}

static int Display_set_new_flags(lua_State *L)
{
	int flags = luaL_checkint(L, 1);
	al_set_new_display_flags(flags);
	return 0;
}

static int Display_set_new_refresh_rate(lua_State *L)
{
	int refresh_rate = luaL_checkint(L, 1);
	al_set_new_display_refresh_rate(refresh_rate);
	return 0;
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
	{"get_num_display_formats",	Display_get_num_display_formats},
	{"get_format_option",	Display_get_format_option},
	{"set_new_format",	Display_set_new_format},
	{"get_new_flags",	Display_get_new_flags},
	{"get_new_refresh_rate",	Display_get_new_refresh_rate},
	{"get_new_window_position",	Display_get_new_window_position},
	{"set_new_option",	Display_set_new_option},
	{"get_new_option",	Display_get_new_option},
	{"reset_new_options",	Display_reset_new_options},
	{"set_new_flags",	Display_set_new_flags},
	{"set_new_refresh_rate",	Display_set_new_refresh_rate},
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
	/* events */
	Set_literal("EVENT_CLOSE", ALLEGRO_EVENT_DISPLAY_CLOSE, -3);
	Set_literal("EVENT_SWITCH_OUT", ALLEGRO_EVENT_DISPLAY_SWITCH_OUT, -3);
	Set_literal("EVENT_RESIZE", ALLEGRO_EVENT_DISPLAY_RESIZE, -3);

	/* flags */
	Set_literal("WINDOWED", ALLEGRO_WINDOWED, -3);
	Set_literal("FULLSCREEN", ALLEGRO_FULLSCREEN, -3);
	Set_literal("RESIZABLE", ALLEGRO_RESIZABLE, -3);
	Set_literal("OPENGL", ALLEGRO_OPENGL, -3);
//	Set_literal("DIRECT3D", ALLEGRO_DIRECT3D, -3);
	Set_literal("NOFRAME", ALLEGRO_NOFRAME, -3);
	
	/* display options */
	Set_literal("RED_SIZE", ALLEGRO_RED_SIZE, -3);
	Set_literal("GREEN_SIZE", ALLEGRO_GREEN_SIZE, -3);
	Set_literal("BLUE_SIZE", ALLEGRO_BLUE_SIZE, -3);
	Set_literal("ALPHA_SIZE", ALLEGRO_ALPHA_SIZE, -3);
	Set_literal("COLOR_SIZE", ALLEGRO_COLOR_SIZE, -3);
	Set_literal("RED_SHIFT", ALLEGRO_RED_SHIFT, -3);
	Set_literal("GREEN_SHIFT", ALLEGRO_GREEN_SHIFT, -3);
	Set_literal("BLUE_SHIFT", ALLEGRO_BLUE_SHIFT, -3);
	Set_literal("ALPHA_SHIFT", ALLEGRO_ALPHA_SHIFT, -3);
	Set_literal("ACC_RED_SIZE", ALLEGRO_ACC_RED_SIZE, -3);
	Set_literal("ACC_GREEN_SIZE", ALLEGRO_ACC_GREEN_SIZE, -3);
	Set_literal("ACC_BLUE_SIZE", ALLEGRO_ACC_BLUE_SIZE, -3);
	Set_literal("ACC_ALPHA_SIZE", ALLEGRO_ACC_ALPHA_SIZE, -3);
	Set_literal("STEREO", ALLEGRO_STEREO, -3);
	Set_literal("AUX_BUFFERS", ALLEGRO_AUX_BUFFERS, -3);
	Set_literal("DEPTH_SIZE", ALLEGRO_DEPTH_SIZE, -3);
	Set_literal("STENCIL_SIZE", ALLEGRO_STENCIL_SIZE, -3);
	Set_literal("SAMPLE_BUFFERS", ALLEGRO_SAMPLE_BUFFERS, -3);
	Set_literal("SAMPLES", ALLEGRO_SAMPLES, -3);
	Set_literal("RENDER_METHOD", ALLEGRO_RENDER_METHOD, -3);
	Set_literal("FLOAT_COLOR", ALLEGRO_FLOAT_COLOR, -3);
	Set_literal("FLOAT_DEPTH", ALLEGRO_FLOAT_DEPTH, -3);
	Set_literal("SINGLE_BUFFER", ALLEGRO_SINGLE_BUFFER, -3);
	Set_literal("SWAP_METHOD", ALLEGRO_SWAP_METHOD, -3);
	Set_literal("COMPATIBLE_DISPLAY", ALLEGRO_COMPATIBLE_DISPLAY, -3);
	Set_literal("UPDATE_DISPLAY_REGION", ALLEGRO_UPDATE_DISPLAY_REGION, -3);
	Set_literal("VSYNC", ALLEGRO_VSYNC, -3);

	/* Option importance */
	Set_literal("REQUIRE", ALLEGRO_REQUIRE, -3);
	Set_literal("SUGGEST", ALLEGRO_SUGGEST, -3);
	Set_literal("DONTCARE", ALLEGRO_DONTCARE, -3);
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
