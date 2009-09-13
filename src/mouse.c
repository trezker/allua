#include "allua/mouse.h"
#include "allua/event_queue.h"
#include "allua/event_source.h"
#include "allua/allua.h"
#include <stdio.h>

#define MOUSE_STRING "mouse"

/* Common handlers
 * */
/*static ALLUA_mouse toMouse (lua_State *L, int index)
{
  ALLUA_mouse *pi = (ALLUA_mouse*)lua_touserdata(L, index);
  if (pi == NULL) luaL_typerror(L, index, MOUSE_STRING);
  return *pi;
}
*/
ALLUA_mouse allua_check_mouse (lua_State *L, int index)
{
  ALLUA_mouse *pi, im;
  luaL_checktype(L, index, LUA_TUSERDATA);
  pi = (ALLUA_mouse*)luaL_checkudata(L, index, MOUSE_STRING);
  if (pi == NULL)
  	luaL_typerror(L, index, MOUSE_STRING);
  im = *pi;
  return im;
}

static ALLUA_mouse *allua_pushMouse (lua_State *L, ALLUA_mouse im)
{
  ALLUA_mouse *pi = (ALLUA_mouse *)lua_newuserdata(L, sizeof(ALLUA_mouse));
  *pi = im;
  luaL_getmetatable(L, MOUSE_STRING);
  lua_setmetatable(L, -2);
  return pi;
}

/* Constructor and methods
 * */

static int allua_mouse_install(lua_State *L)
{
	lua_pushboolean(L, al_install_mouse());
	return 1;
}

static int allua_mouse_uninstall(lua_State *L)
{
	al_uninstall_mouse();
	return 0;
}

static int allua_mouse_is_installed(lua_State *L)
{
	lua_pushboolean(L, al_is_mouse_installed());
	return 1;
}

static int allua_mouse_get_event_source(lua_State *L)
{
	allua_pushevent_source(L, al_get_mouse_event_source());
	return 1;
}
/*
static int allua_mouse_get(lua_State *L)
{
	allua_pushMouse(L, al_get_mouse());
	return 1;
}
*/
static int allua_mouse_get_cursor_position(lua_State *L)
{
	int x;
	int y;
	if(al_get_mouse_cursor_position(&x, &y))
	{
		lua_pushinteger(L, x);
		lua_pushinteger(L, y);
		return 2;
	}
	lua_pushnil(L);
	return 1;
}

static int allua_mouse_get_num_axes(lua_State *L)
{
	lua_pushinteger(L, al_get_mouse_num_axes());
	return 1;
}

static int allua_mouse_get_num_buttons(lua_State *L)
{
	lua_pushinteger(L, al_get_mouse_num_buttons());
	return 1;
}

static int allua_mouse_hide_cursor(lua_State *L)
{
	lua_pushboolean(L, al_hide_mouse_cursor());
	return 1;
}

static int allua_mouse_show_cursor(lua_State *L)
{
	lua_pushboolean(L, al_show_mouse_cursor());
	return 1;
}

static int allua_mouse_set_axis(lua_State *L)
{
	int which = luaL_checkint(L, 1);
	int value = luaL_checkint(L, 2);
	lua_pushboolean(L, al_set_mouse_axis(which, value));
	return 1;
}

static int allua_mouse_set_range(lua_State *L)
{
	int x1 = luaL_checkint(L, 1);
	int y1 = luaL_checkint(L, 2);
	int x2 = luaL_checkint(L, 3);
	int y2 = luaL_checkint(L, 4);
	lua_pushboolean(L, al_set_mouse_range(x1, y1, x2, y2));
	return 1;
}

static int allua_mouse_set_w(lua_State *L)
{
	int w = luaL_checkint(L, 1);
	lua_pushboolean(L, al_set_mouse_w(w));
	return 1;
}

static int allua_mouse_set_xy(lua_State *L)
{
	int x = luaL_checkint(L, 1);
	int y = luaL_checkint(L, 2);
	lua_pushboolean(L, al_set_mouse_xy(x, y));
	return 1;
}

static const luaL_reg allua_Mouse_methods[] = {
  {"install",           allua_mouse_install},
  {"uninstall",           allua_mouse_uninstall},
  {"is_installed",           allua_mouse_is_installed},
  {"get_event_source",           allua_mouse_get_event_source},
//  {"get",           allua_mouse_get},
  {"get_cursor_position",           allua_mouse_get_cursor_position},
  {"get_num_axes",           allua_mouse_get_num_axes},
  {"get_num_buttons",           allua_mouse_get_num_buttons},
  {"hide_cursor",           allua_mouse_hide_cursor},
  {"show_cursor",           allua_mouse_show_cursor},
  {"set_axis",           allua_mouse_set_axis},
  {"set_range",           allua_mouse_set_range},
  {"set_w",           allua_mouse_set_w},
  {"set_z",           allua_mouse_set_w},
  {"set_xy",           allua_mouse_set_xy},
  {0,0}
};

/* GC and meta
 * */
static int allua_Mouse_tostring (lua_State *L)
{
  lua_pushfstring(L, "mouse: %p", lua_touserdata(L, 1));
  return 1;
}

static const luaL_reg allua_Mouse_meta[] = {
  {"__tostring", allua_Mouse_tostring},
  {0, 0}
};

/* Event callbacks
 * */
void allua_mouse_event_callback(lua_State *L, ALLEGRO_EVENT *event)
{
	Set_literal("x", event->mouse.x, -3);
	Set_literal("y", event->mouse.y, -3);
	Set_literal("z", event->mouse.z, -3);

	if(event->type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		Set_literal("dx", event->mouse.dx, -3);
		Set_literal("dy", event->mouse.dy, -3);
		Set_literal("dz", event->mouse.dz, -3);
	}
	if(event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN
	|| event->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	{
		Set_literal("button", event->mouse.button, -3);
	}
}

/* Other attributes
 * */
void allua_Mouse_set_attributes(lua_State *L)
{
	Set_literal("EVENT_AXES", ALLEGRO_EVENT_MOUSE_AXES, -3);
	Set_literal("EVENT_DOWN", ALLEGRO_EVENT_MOUSE_BUTTON_DOWN, -3);
	Set_literal("EVENT_UP", ALLEGRO_EVENT_MOUSE_BUTTON_UP, -3);
	Set_literal("EVENT_ENTER_DISPLAY", ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY, -3);
	Set_literal("EVENT_LEAVE_DISPLAY", ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY, -3);
}

/* Register
 * */
int allua_register_mouse (lua_State *L)
{
	allua_set_event_callback(ALLEGRO_EVENT_MOUSE_AXES, allua_mouse_event_callback);
	allua_set_event_callback(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN, allua_mouse_event_callback);
	allua_set_event_callback(ALLEGRO_EVENT_MOUSE_BUTTON_UP, allua_mouse_event_callback);
	allua_set_event_callback(ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY, allua_mouse_event_callback);
	allua_set_event_callback(ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY, allua_mouse_event_callback);

  lua_newtable(L);
  luaL_register(L, NULL, allua_Mouse_methods);  /* create methods table,
                                                add it to the globals */

	allua_Mouse_set_attributes(L);

  luaL_newmetatable(L, MOUSE_STRING);        /* create metatable for Image,
                                         add it to the Lua registry */
  luaL_register(L, 0, allua_Mouse_meta);  /* fill metatable */
  lua_pushliteral(L, "__index");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* metatable.__index = methods */
  lua_pushliteral(L, "__metatable");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* hide metatable:
                                         metatable.__metatable = methods */
  lua_pop(L, 1);                      /* drop metatable */

  lua_setfield(L, -2, MOUSE_STRING);

  return 0;                           /* return methods on the stack */
}
