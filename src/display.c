#include "allua/display.h"
#include "allua/bitmap.h"
#include "allua/allua.h"
#include "allua/color.h"
#include "allua/event_queue.h"
#include "allua/event_source.h"

//#include <allegro5/a5_direct3d.h>
#include <allegro5/a5_opengl.h>
#include <stdio.h>

#define DISPLAY_STRING "display"

/* Common handlers
 * */
static ALLUA_display allua_todisplay (lua_State *L, int index)
{
  ALLUA_display *pi = (ALLUA_display*)lua_touserdata(L, index);
  if (pi == NULL) luaL_typerror(L, index, DISPLAY_STRING);
  return *pi;
}

ALLUA_display allua_check_display (lua_State *L, int index)
{
  ALLUA_display *pi, im;
  luaL_checktype(L, index, LUA_TUSERDATA);
  pi = (ALLUA_display*)luaL_checkudata(L, index, DISPLAY_STRING);
  if (pi == NULL)
  	luaL_typerror(L, index, DISPLAY_STRING);
  im = *pi;
  if (!im)
    luaL_error(L, "null display");
  return im;
}

static ALLUA_display *allua_pushdisplay (lua_State *L, ALLUA_display im)
{
	lua_getfield (L, LUA_REGISTRYINDEX, "allegro5udatamap");
    lua_pushlightuserdata(L, (void *)im);  // push address 
    lua_gettable(L, -2);  // retrieve value 

	ALLUA_display *pi;
	if(!lua_isnil (L, -1))
	{
		pi = lua_touserdata (L, -1);
	}
	else
	{
		lua_pop(L, 1); //Pop the nil
		// Create new userdata
		lua_pushlightuserdata(L, (void *)im); //Key
		pi = (ALLUA_display *)lua_newuserdata(L, sizeof(ALLUA_display)); //value
		*pi = im;
		luaL_getmetatable(L, DISPLAY_STRING);
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
static int allua_display_create (lua_State *L)
{
  int w = luaL_checkint(L, 1);
  int h = luaL_checkint(L, 2);
  allua_pushdisplay(L, al_create_display(w, h));
  return 1;
}

static int allua_display_get_event_source(lua_State *L)
{
	ALLUA_display display = allua_check_display(L, 1);
	allua_pushevent_source(L, al_get_display_event_source(display));
	return 1;
}

static int allua_display_get_num_display_formats(lua_State *L)
{
	lua_pushnumber(L, al_get_num_display_formats());
	return 1;
}

static int allua_display_get_format_option(lua_State *L)
{
	int i = luaL_checkint(L, 1);
	int option = luaL_checkint(L, 2);
	lua_pushnumber(L, al_get_display_format_option(i, option));
	return 1;
}

static int allua_display_set_new_format(lua_State *L)
{
	int i = luaL_checkint(L, 1);
	al_set_new_display_format(i);
	return 0;
}

static int allua_display_get_new_flags(lua_State *L)
{
	lua_pushnumber(L, al_get_new_display_flags());
	return 1;
}

static int allua_display_get_new_refresh_rate(lua_State *L)
{
	lua_pushnumber(L, al_get_new_display_refresh_rate());
	return 1;
}

static int allua_display_get_new_window_position(lua_State *L)
{
	int x;
	int y;
	al_get_new_window_position(&x, &y);
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);
	return 2;
}

static int allua_display_set_new_option(lua_State *L)
{
	int option = luaL_checkint(L, 1);
	int value = luaL_checkint(L, 2);
	int importance = luaL_checkint(L, 3);
	al_set_new_display_option(option, value, importance);
	return 0;
}

static int allua_display_get_new_option(lua_State *L)
{
	int option = luaL_checkint(L, 1);
	int importance;
	int value = al_get_new_display_option(option, &importance);
	lua_pushnumber(L, value);
	lua_pushnumber(L, importance);
	return 2;
}

static int allua_display_reset_new_options(lua_State *L)
{
	al_reset_new_display_options();
	return 0;
}

static int allua_display_set_new_flags(lua_State *L)
{
	int flags = luaL_checkint(L, 1);
	al_set_new_display_flags(flags);
	return 0;
}

static int allua_display_set_new_refresh_rate(lua_State *L)
{
	int refresh_rate = luaL_checkint(L, 1);
	al_set_new_display_refresh_rate(refresh_rate);
	return 0;
}

static int allua_display_set_new_window_position(lua_State *L)
{
	int x = luaL_checkint(L, 1);
	int y = luaL_checkint(L, 2);
	al_set_new_window_position(x, y);
	return 0;
}

static int allua_display_flip (lua_State *L)
{
	al_flip_display();
	return 0;
}

static int allua_display_get_backbuffer (lua_State *L)
{
	allua_pushBitmap(L, al_get_backbuffer(), false);
	return 1;
}

static int allua_display_get_frontbuffer (lua_State *L)
{
	ALLEGRO_BITMAP* fb = al_get_frontbuffer();
	fb ? allua_pushBitmap(L, fb, false): lua_pushnil(L);
	return 1;
}

static int allua_display_get_current (lua_State *L)
{
	allua_pushdisplay(L, al_get_current_display());
	return 1;
}

static int allua_display_get_flags (lua_State *L)
{
	lua_pushnumber(L, al_get_display_flags());
	return 1;
}

static int allua_display_get_format (lua_State *L)
{
	lua_pushnumber(L, al_get_display_format());
	return 1;
}

static int allua_display_get_refresh_rate (lua_State *L)
{
	lua_pushnumber(L, al_get_display_refresh_rate());
	return 1;
}

static int allua_display_get_window_position (lua_State *L)
{
	ALLUA_display display = allua_check_display(L, 1);
	int x;
	int y;
	al_get_window_position(display, &x, &y);
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);
	return 2;
}

static int allua_display_inhibit_screensaver (lua_State *L)
{
	int inhibit = lua_toboolean(L, 1);
	lua_pushboolean(L, al_inhibit_screensaver(inhibit));
	return 1;
}

static int allua_display_resize (lua_State *L)
{
	int width = luaL_checkint(L, 1);
	int height = luaL_checkint(L, 2);
	lua_pushboolean(L, al_resize_display(width, height));
	return 1;
}

static int allua_display_set_current (lua_State *L)
{
	ALLUA_display display = allua_check_display(L, 1);
	lua_pushboolean(L, al_set_current_display(display));
	return 1;
}

static int allua_display_acknowledge_resize (lua_State *L)
{
	ALLUA_display display = allua_check_display(L, 1);
	lua_pushboolean(L, al_acknowledge_resize(display));
	return 1;
}

static int allua_display_set_icon (lua_State *L)
{
	ALLUA_bitmap bmp = allua_check_bitmap(L, 1);
	al_set_display_icon(bmp);
	return 0;
}

static int allua_display_get_option (lua_State *L)
{
	int option = luaL_checkint(L, 1);
	lua_pushnumber(L, al_get_display_option(option));
	return 1;
}

static int allua_display_set_window_position (lua_State *L)
{
	ALLUA_display display = allua_check_display(L, 1);
	int x = luaL_checkint(L, 2);
	int y = luaL_checkint(L, 3);

	al_set_window_position(display, x, y);
	return 0;
}

static int allua_display_set_window_title (lua_State *L)
{
	const char* title = luaL_checkstring(L, 1);

	al_set_window_title(title);
	return 0;
}

static int allua_display_toggle_window_frame (lua_State *L)
{
	ALLUA_display display = allua_check_display(L, 1);
	int onoff = lua_toboolean(L, 2);

	al_toggle_window_frame(display, onoff);
	return 0;
}

static int allua_display_update_region (lua_State *L)
{
	int x = luaL_checkint(L, 1);
	int y = luaL_checkint(L, 2);
	int w = luaL_checkint(L, 3);
	int h = luaL_checkint(L, 4);

	al_update_display_region(x, y, w, h);
	return 0;
}

static int allua_display_wait_for_vsync (lua_State *L)
{
	lua_pushboolean(L, al_wait_for_vsync());
	return 1;
}

static int allua_display_get_num_modes (lua_State *L)
{
	lua_pushinteger(L, al_get_num_display_modes());
	return 1;
}

static int allua_display_get_mode (lua_State *L)
{
	int index = luaL_checkint(L, 1);
	ALLEGRO_DISPLAY_MODE m;
	ALLEGRO_DISPLAY_MODE* rm = al_get_display_mode(index, &m);
	if(!rm)
	{
		lua_pushnil(L);
	}
	else
	{
		lua_newtable(L);
		lua_pushinteger(L, rm->width);
		lua_setfield(L, -2, "width");
		lua_pushinteger(L, rm->height);
		lua_setfield(L, -2, "height");
		lua_pushinteger(L, rm->format);
		lua_setfield(L, -2, "format");
		lua_pushinteger(L, rm->refresh_rate);
		lua_setfield(L, -2, "refresh_rate");
	}
	return 1;
}

static int allua_display_get_current_video_adapter (lua_State *L)
{
	lua_pushinteger(L, al_get_current_video_adapter());
	return 1;
}

static int allua_display_set_current_video_adapter (lua_State *L)
{
	int index = luaL_checkint(L, 1);
	al_set_current_video_adapter(index);
	return 0;
}

static int allua_display_get_num_video_adapters (lua_State *L)
{
	lua_pushinteger(L, al_get_num_video_adapters());
	return 1;
}

static int allua_display_get_monitor_info (lua_State *L)
{
	int index = luaL_checkint(L, 1);
	ALLEGRO_MONITOR_INFO info;
	al_get_monitor_info(index, &info);
	lua_newtable(L);
	lua_pushinteger(L, info.x1);
	lua_setfield(L, -2, "x1");
	lua_pushinteger(L, info.y1);
	lua_setfield(L, -2, "y1");
	lua_pushinteger(L, info.x2);
	lua_setfield(L, -2, "x2");
	lua_pushinteger(L, info.y2);
	lua_setfield(L, -2, "y2");
	return 1;
}

static int allua_display_get_height(lua_State *L)
{
	lua_pushinteger(L, al_get_display_height());
	return 1;
}

static int allua_display_get_width(lua_State *L)
{
	lua_pushinteger(L, al_get_display_width());
	return 1;
}

static const luaL_reg allua_display_methods[] = {
	{"create",           allua_display_create},
	{"get_event_source",	allua_display_get_event_source},
	{"get_num_display_formats",	allua_display_get_num_display_formats},
	{"get_format_option",	allua_display_get_format_option},
	{"set_new_format",	allua_display_set_new_format},
	{"get_new_flags",	allua_display_get_new_flags},
	{"get_new_refresh_rate",	allua_display_get_new_refresh_rate},
	{"get_new_window_position",	allua_display_get_new_window_position},
	{"set_new_option",	allua_display_set_new_option},
	{"get_new_option",	allua_display_get_new_option},
	{"reset_new_options",	allua_display_reset_new_options},
	{"set_new_flags",	allua_display_set_new_flags},
	{"set_new_refresh_rate",	allua_display_set_new_refresh_rate},
	{"set_new_window_position",	allua_display_set_new_window_position},
	{"acknowledge_resize",           allua_display_acknowledge_resize},
	{"flip",           allua_display_flip},
	{"get_backbuffer",           allua_display_get_backbuffer},
	{"get_current",           allua_display_get_current},
	{"get_flags",           allua_display_get_flags},
	{"get_format",           allua_display_get_format},
	{"get_height",           allua_display_get_height},
	{"get_refresh_rate",           allua_display_get_refresh_rate},
	{"get_width",           allua_display_get_width},
	{"get_frontbuffer",           allua_display_get_frontbuffer},
	{"get_window_position",           allua_display_get_window_position},
	{"inhibit_screensaver",           allua_display_inhibit_screensaver},
	{"resize",           allua_display_resize},
	{"set_current",           allua_display_set_current},
	{"set_icon",           allua_display_set_icon},
	{"get_option",           allua_display_get_option},
	{"set_window_position",           allua_display_set_window_position},
	{"set_window_title",           allua_display_set_window_title},
	{"toggle_window_frame",           allua_display_toggle_window_frame},
	{"update_region",           allua_display_update_region},
	{"wait_for_vsync",           allua_display_wait_for_vsync},
	{"get_num_modes",           allua_display_get_num_modes},
	{"get_mode",           allua_display_get_mode},
	{"get_current_video_adapter",           allua_display_get_current_video_adapter},
	{"set_current_video_adapter",           allua_display_set_current_video_adapter},
	{"get_num_video_adapters",           allua_display_get_num_video_adapters},
	{"get_monitor_info",           allua_display_get_monitor_info},
	{0,0}
};

/* GC and meta
 * */
static int allua_display_gc (lua_State *L)
{
  ALLUA_display im = allua_todisplay(L, 1);
  printf("goodbye display (%p)\n", im);
  if (im) al_destroy_display(im);
  return 0;
}

static int allua_display_tostring (lua_State *L)
{
  lua_pushfstring(L, "display: %p", lua_touserdata(L, 1));
  return 1;
}

static const luaL_reg allua_display_meta[] = {
  {"__gc",       allua_display_gc},
  {"__tostring", allua_display_tostring},
  {0, 0}
};

/* Event callbacks
 * */
void allua_display_event_callback(lua_State *L, ALLEGRO_EVENT *event)
{
	printf("Allegro event source: %p \n",event->display.source);
	allua_pushdisplay(L, event->display.source);
	lua_setfield(L, -2, "source");

	Set_literal("x", event->display.x, -3);
	Set_literal("y", event->display.y, -3);
	Set_literal("width", event->display.width, -3);
	Set_literal("height", event->display.height, -3);
}

/* Other attributes
 * */
void allua_display_set_attributes(lua_State *L)
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
int allua_register_display (lua_State *L)
{
	allua_set_event_callback(ALLEGRO_EVENT_DISPLAY_RESIZE, allua_display_event_callback);
	allua_set_event_callback(ALLEGRO_EVENT_DISPLAY_CLOSE, allua_display_event_callback);

  lua_newtable(L);
  luaL_register(L, NULL, allua_display_methods);  /* create methods table,
                                                add it to the globals */

	allua_display_set_attributes(L);

  luaL_newmetatable(L, DISPLAY_STRING);        /* create metatable for Image,
                                         add it to the Lua registry */
  luaL_register(L, 0, allua_display_meta);  /* fill metatable */
  lua_pushliteral(L, "__index");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* metatable.__index = methods */
  lua_pushliteral(L, "__metatable");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* hide metatable:
                                         metatable.__metatable = methods */
  lua_pop(L, 1);                      /* drop metatable */

  lua_setfield(L, -2, DISPLAY_STRING);

  return 0;                           /* return methods on the stack */
}
