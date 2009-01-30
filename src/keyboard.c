#include "keyboard.h"
#include "event_queue.h"
#include "al_lua.h"
#include <stdio.h>

#define KEYBOARD "Keyboard"

/* Common handlers
 * */
static AL_Keyboard toKeyboard (lua_State *L, int index)
{
  AL_Keyboard *pi = (AL_Keyboard*)lua_touserdata(L, index);
  if (pi == NULL) luaL_typerror(L, index, KEYBOARD);
  return *pi;
}

AL_Keyboard al_lua_check_keyboard (lua_State *L, int index)
{
  AL_Keyboard *pi, im;
  luaL_checktype(L, index, LUA_TUSERDATA);
  pi = (AL_Keyboard*)luaL_checkudata(L, index, KEYBOARD);
  if (pi == NULL)
  	luaL_typerror(L, index, KEYBOARD);
  im = *pi;
  return im;
}

static AL_Keyboard *pushKeyboard (lua_State *L, AL_Keyboard im)
{
  AL_Keyboard *pi = (AL_Keyboard *)lua_newuserdata(L, sizeof(AL_Keyboard));
  *pi = im;
  luaL_getmetatable(L, KEYBOARD);
  lua_setmetatable(L, -2);
  return pi;
}

/* Constructor and methods
 * */
static int al_lua_get_keyboard(lua_State *L)
{
	pushKeyboard(L, al_get_keyboard());
	return 1;
}

static int al_lua_keycode_to_name(lua_State *L)
{
	int keycode = luaL_checkint(L, 1);
	lua_pushstring(L, al_keycode_to_name(keycode));
	return 1;
}

static const luaL_reg Keyboard_methods[] = {
  {"get",           al_lua_get_keyboard},
  {"keycode_to_name",           al_lua_keycode_to_name},
  {0,0}
};

/* GC and meta
 * */
static int Keyboard_tostring (lua_State *L)
{
  lua_pushfstring(L, "Keyboard: %p", lua_touserdata(L, 1));
  return 1;
}

static const luaL_reg Keyboard_meta[] = {
  {"__tostring", Keyboard_tostring},
  {0, 0}
};

/* Event callbacks
 * */
void al_lua_keyboard_event_callback(lua_State *L, ALLEGRO_EVENT *event)
{
	Set_literal("keycode", event->keyboard.keycode, -3);
	if(event->type != ALLEGRO_EVENT_KEY_UP)
	{
		Set_literal("unichar", event->keyboard.unichar, -3);
		Set_literal("modifiers", event->keyboard.modifiers, -3);
	}
}

/* Other attributes
 * */
void Keyboard_set_attributes(lua_State *L)
{
	Set_literal("EVENT_DOWN", ALLEGRO_EVENT_KEY_DOWN, -3);
	Set_literal("EVENT_REPEAT", ALLEGRO_EVENT_KEY_REPEAT, -3);
	Set_literal("EVENT_UP", ALLEGRO_EVENT_KEY_UP, -3);

	//Todo: Complete keycode constants
	Set_literal("KEY_ESCAPE", ALLEGRO_KEY_ESCAPE, -3);

	char key[6] = "KEY_A";
	int i;
	for(i = ALLEGRO_KEY_A; i <= ALLEGRO_KEY_Z; ++i)
	{
		key[4] = 'A' + (i-ALLEGRO_KEY_A);
		Set_string(key, i, -3);
	}
}

/* Register
 * */
int al_lua_register_keyboard (lua_State *L)
{
	al_lua_set_event_callback(ALLEGRO_EVENT_KEY_DOWN, al_lua_keyboard_event_callback);
	al_lua_set_event_callback(ALLEGRO_EVENT_KEY_REPEAT, al_lua_keyboard_event_callback);
	al_lua_set_event_callback(ALLEGRO_EVENT_KEY_UP, al_lua_keyboard_event_callback);

  luaL_register(L, KEYBOARD, Keyboard_methods);  /* create methods table,
                                                add it to the globals */

	Keyboard_set_attributes(L);

  luaL_newmetatable(L, KEYBOARD);        /* create metatable for Image,
                                         add it to the Lua registry */
  luaL_register(L, 0, Keyboard_meta);  /* fill metatable */
  lua_pushliteral(L, "__index");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* metatable.__index = methods */
  lua_pushliteral(L, "__metatable");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* hide metatable:
                                         metatable.__metatable = methods */
  lua_pop(L, 1);                      /* drop metatable */

  return 1;                           /* return methods on the stack */
}
