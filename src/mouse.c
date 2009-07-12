#include "allua/mouse.h"
#include "allua/event_queue.h"
#include "allua/al_lua.h"
#include <stdio.h>

#define MOUSE "mouse"

/* Common handlers
 * */
/*static AL_mouse toMouse (lua_State *L, int index)
{
  AL_mouse *pi = (AL_mouse*)lua_touserdata(L, index);
  if (pi == NULL) luaL_typerror(L, index, MOUSE);
  return *pi;
}
*/
AL_mouse al_lua_check_mouse (lua_State *L, int index)
{
  AL_mouse *pi, im;
  luaL_checktype(L, index, LUA_TUSERDATA);
  pi = (AL_mouse*)luaL_checkudata(L, index, MOUSE);
  if (pi == NULL)
  	luaL_typerror(L, index, MOUSE);
  im = *pi;
  return im;
}

static AL_mouse *pushMouse (lua_State *L, AL_mouse im)
{
  AL_mouse *pi = (AL_mouse *)lua_newuserdata(L, sizeof(AL_mouse));
  *pi = im;
  luaL_getmetatable(L, MOUSE);
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

static int allua_mouse_is_installed(lua_State *L)
{
	lua_pushboolean(L, al_is_mouse_installed());
	return 1;
}

static int allua_mouse_get(lua_State *L)
{
	pushMouse(L, al_get_mouse());
	return 1;
}

static int allua_mouse_get_cursor_position(lua_State *L)
{
	int x;
	int y;
	if(al_get_cursor_position(&x, &y))
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

static const luaL_reg Mouse_methods[] = {
  {"install",           allua_mouse_install},
  {"is_installed",           allua_mouse_is_installed},
  {"get",           allua_mouse_get},
  {"get_cursor_position",           allua_mouse_get_cursor_position},
  {"get_num_axes",           allua_mouse_get_num_axes},
  {"get_num_buttons",           allua_mouse_get_num_buttons},
  {"hide_cursor",           allua_mouse_hide_cursor},
  {0,0}
};

/* GC and meta
 * */
static int Mouse_tostring (lua_State *L)
{
  lua_pushfstring(L, "Mouse: %p", lua_touserdata(L, 1));
  return 1;
}

static const luaL_reg Mouse_meta[] = {
  {"__tostring", Mouse_tostring},
  {0, 0}
};

/* Event callbacks
 * */
void al_lua_mouse_event_callback(lua_State *L, ALLEGRO_EVENT *event)
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
void Mouse_set_attributes(lua_State *L)
{
	Set_literal("EVENT_AXES", ALLEGRO_EVENT_MOUSE_AXES, -3);
	Set_literal("EVENT_DOWN", ALLEGRO_EVENT_MOUSE_BUTTON_DOWN, -3);
	Set_literal("EVENT_UP", ALLEGRO_EVENT_MOUSE_BUTTON_UP, -3);
	Set_literal("EVENT_ENTER_DISPLAY", ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY, -3);
	Set_literal("EVENT_LEAVE_DISPLAY", ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY, -3);
}

/* Register
 * */
int al_lua_register_mouse (lua_State *L)
{
	al_lua_set_event_callback(ALLEGRO_EVENT_MOUSE_AXES, al_lua_mouse_event_callback);
	al_lua_set_event_callback(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN, al_lua_mouse_event_callback);
	al_lua_set_event_callback(ALLEGRO_EVENT_MOUSE_BUTTON_UP, al_lua_mouse_event_callback);
	al_lua_set_event_callback(ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY, al_lua_mouse_event_callback);
	al_lua_set_event_callback(ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY, al_lua_mouse_event_callback);

  lua_newtable(L);
  luaL_register(L, NULL, Mouse_methods);  /* create methods table,
                                                add it to the globals */

	Mouse_set_attributes(L);

  luaL_newmetatable(L, MOUSE);        /* create metatable for Image,
                                         add it to the Lua registry */
  luaL_register(L, 0, Mouse_meta);  /* fill metatable */
  lua_pushliteral(L, "__index");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* metatable.__index = methods */
  lua_pushliteral(L, "__metatable");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* hide metatable:
                                         metatable.__metatable = methods */
  lua_pop(L, 1);                      /* drop metatable */

  lua_setfield(L, -2, MOUSE);

  return 0;                           /* return methods on the stack */
}
