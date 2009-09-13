#include "allua/keyboard.h"
#include "allua/event_queue.h"
#include "allua/event_source.h"
#include "allua/allua.h"
#include <stdio.h>

#define KEYBOARD_STRING "keyboard"

/* Common handlers
 * */
/*static ALLUA_keyboard toKeyboard (lua_State *L, int index)
{
  ALLUA_keyboard *pi = (ALLUA_keyboard*)lua_touserdata(L, index);
  if (pi == NULL) luaL_typerror(L, index, KEYBOARD_STRING);
  return *pi;
}
*/
ALLUA_keyboard allua_check_keyboard (lua_State *L, int index)
{
  ALLUA_keyboard *pi, im;
  luaL_checktype(L, index, LUA_TUSERDATA);
  pi = (ALLUA_keyboard*)luaL_checkudata(L, index, KEYBOARD_STRING);
  if (pi == NULL)
  	luaL_typerror(L, index, KEYBOARD_STRING);
  im = *pi;
  return im;
}
/*
static ALLUA_keyboard *allua_pushKeyboard (lua_State *L, ALLUA_keyboard im)
{
  ALLUA_keyboard *pi = (ALLUA_keyboard *)lua_newuserdata(L, sizeof(ALLUA_keyboard));
  *pi = im;
  luaL_getmetatable(L, KEYBOARD_STRING);
  lua_setmetatable(L, -2);
  return pi;
}
*/
/* Constructor and methods
 * */

static int allua_keyboard_install(lua_State *L)
{
	lua_pushboolean(L, al_install_keyboard());
	return 1;
}

static int allua_keyboard_uninstall(lua_State *L)
{
	al_uninstall_keyboard();
	return 0;
}

static int allua_keyboard_is_installed(lua_State *L)
{
	lua_pushboolean(L, al_is_keyboard_installed());
	return 1;
}

static int allua_keyboard_get_event_source(lua_State *L)
{
	allua_pushevent_source(L, al_get_keyboard_event_source());
	return 1;
}

static int allua_keyboard_set_leds(lua_State *L)
{
	int leds = luaL_checkint(L, 1);
	lua_pushboolean(L, al_set_keyboard_leds(leds));
	return 1;
}
/*
static int allua_get_keyboard(lua_State *L)
{
	allua_pushKeyboard(L, al_get_keyboard());
	return 1;
}
*/
static int allua_keycode_to_name(lua_State *L)
{
	int keycode = luaL_checkint(L, 1);
	lua_pushstring(L, al_keycode_to_name(keycode));
	return 1;
}

static int allua_keycode_from_name(lua_State *L)
{
	const char *keyname = luaL_checkstring(L, 1);

	int keycode = 0;
	int i = 0;
	for(; i < ALLEGRO_KEY_MAX; ++i)
	{
		if(!strncmp(al_keycode_to_name(i), keyname, 32))
		{
			keycode = i;
		}
	}
	lua_pushinteger(L, keycode);
	return 1;
}

static const luaL_reg allua_Keyboard_methods[] = {
  {"install",           allua_keyboard_install},
  {"uninstall",           allua_keyboard_uninstall},
  {"is_installed",           allua_keyboard_is_installed},
  {"get_event_source",           allua_keyboard_get_event_source},
  {"set_leds",           allua_keyboard_set_leds},
//  {"get",           allua_get_keyboard},
  {"keycode_to_name",           allua_keycode_to_name},
  {"keycode_from_name",           allua_keycode_from_name},
  {0,0}
};

/* GC and meta
 * */
static int allua_Keyboard_tostring (lua_State *L)
{
  lua_pushfstring(L, "keyboard: %p", lua_touserdata(L, 1));
  return 1;
}

static const luaL_reg allua_Keyboard_meta[] = {
  {"__tostring", allua_Keyboard_tostring},
  {0, 0}
};

/* Event callbacks
 * */
void allua_keyboard_event_callback(lua_State *L, ALLEGRO_EVENT *event)
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
void allua_Keyboard_set_attributes(lua_State *L)
{
	Set_literal("EVENT_DOWN", ALLEGRO_EVENT_KEY_DOWN, -3);
	Set_literal("EVENT_REPEAT", ALLEGRO_EVENT_KEY_REPEAT, -3);
	Set_literal("EVENT_UP", ALLEGRO_EVENT_KEY_UP, -3);

	//Keycode constants
	Set_literal("KEY_ESCAPE", ALLEGRO_KEY_ESCAPE, -3);
	Set_literal("KEY_DOWN", ALLEGRO_KEY_DOWN, -3);
	Set_literal("KEY_UP", ALLEGRO_KEY_UP, -3);
	Set_literal("KEY_LEFT", ALLEGRO_KEY_LEFT, -3);
	Set_literal("KEY_RIGHT", ALLEGRO_KEY_RIGHT, -3);
	Set_literal("KEY_SPACE", ALLEGRO_KEY_SPACE, -3);
	Set_literal("KEY_ENTER", ALLEGRO_KEY_ENTER, -3);
	Set_literal("KEY_PAD_ENTER", ALLEGRO_KEY_PAD_ENTER, -3);

	char key[6] = "KEY_A";
	int i;
	for(i = ALLEGRO_KEY_A; i <= ALLEGRO_KEY_Z; ++i)
	{
		key[4] = 'A' + (i-ALLEGRO_KEY_A);
		Set_string(key, i, -3);
	}

	Set_literal("KEY_0", ALLEGRO_KEY_0, -3);
	Set_literal("KEY_1", ALLEGRO_KEY_1, -3);
	Set_literal("KEY_2", ALLEGRO_KEY_2, -3);
	Set_literal("KEY_3", ALLEGRO_KEY_3, -3);
	Set_literal("KEY_4", ALLEGRO_KEY_4, -3);
	Set_literal("KEY_5", ALLEGRO_KEY_5, -3);
	Set_literal("KEY_6", ALLEGRO_KEY_6, -3);
	Set_literal("KEY_7", ALLEGRO_KEY_7, -3);
	Set_literal("KEY_8", ALLEGRO_KEY_8, -3);
	Set_literal("KEY_9", ALLEGRO_KEY_9, -3);

	Set_literal("KEY_PAD_0", ALLEGRO_KEY_PAD_0, -3);
	Set_literal("KEY_PAD_1", ALLEGRO_KEY_PAD_1, -3);
	Set_literal("KEY_PAD_2", ALLEGRO_KEY_PAD_2, -3);
	Set_literal("KEY_PAD_3", ALLEGRO_KEY_PAD_3, -3);
	Set_literal("KEY_PAD_4", ALLEGRO_KEY_PAD_4, -3);
	Set_literal("KEY_PAD_5", ALLEGRO_KEY_PAD_5, -3);
	Set_literal("KEY_PAD_6", ALLEGRO_KEY_PAD_6, -3);
	Set_literal("KEY_PAD_7", ALLEGRO_KEY_PAD_7, -3);
	Set_literal("KEY_PAD_8", ALLEGRO_KEY_PAD_8, -3);
	Set_literal("KEY_PAD_9", ALLEGRO_KEY_PAD_9, -3);

	Set_literal("KEY_F1", ALLEGRO_KEY_F1, -3);
	Set_literal("KEY_F2", ALLEGRO_KEY_F2, -3);
	Set_literal("KEY_F3", ALLEGRO_KEY_F3, -3);
	Set_literal("KEY_F4", ALLEGRO_KEY_F4, -3);
	Set_literal("KEY_F5", ALLEGRO_KEY_F5, -3);
	Set_literal("KEY_F6", ALLEGRO_KEY_F6, -3);
	Set_literal("KEY_F7", ALLEGRO_KEY_F7, -3);
	Set_literal("KEY_F8", ALLEGRO_KEY_F8, -3);
	Set_literal("KEY_F9", ALLEGRO_KEY_F9, -3);
	Set_literal("KEY_F10", ALLEGRO_KEY_F10, -3);
	Set_literal("KEY_F11", ALLEGRO_KEY_F11, -3);
	Set_literal("KEY_F12", ALLEGRO_KEY_F12, -3);

	Set_literal("KEY_TILDE", ALLEGRO_KEY_TILDE, -3);
	Set_literal("KEY_MINUS", ALLEGRO_KEY_MINUS, -3);
	Set_literal("KEY_EQUALS", ALLEGRO_KEY_EQUALS, -3);
	Set_literal("KEY_BACKSPACE", ALLEGRO_KEY_BACKSPACE, -3);
	Set_literal("KEY_TAB", ALLEGRO_KEY_TAB, -3);
	Set_literal("KEY_OPENBRACE", ALLEGRO_KEY_OPENBRACE, -3);
	Set_literal("KEY_CLOSEBRACE", ALLEGRO_KEY_CLOSEBRACE, -3);
	Set_literal("KEY_SEMICOLON", ALLEGRO_KEY_SEMICOLON, -3);
	Set_literal("KEY_QUOTE", ALLEGRO_KEY_QUOTE, -3);
	Set_literal("KEY_BACKSLASH", ALLEGRO_KEY_BACKSLASH, -3);
	Set_literal("KEY_BACKSLASH2", ALLEGRO_KEY_BACKSLASH2, -3);
	Set_literal("KEY_COMMA", ALLEGRO_KEY_COMMA, -3);
	Set_literal("KEY_FULLSTOP", ALLEGRO_KEY_FULLSTOP, -3);
	Set_literal("KEY_SLASH", ALLEGRO_KEY_SLASH, -3);
	Set_literal("KEY_INSERT", ALLEGRO_KEY_INSERT, -3);
	Set_literal("KEY_DELETE", ALLEGRO_KEY_DELETE, -3);
	Set_literal("KEY_HOME", ALLEGRO_KEY_HOME, -3);
	Set_literal("KEY_END", ALLEGRO_KEY_END, -3);
	Set_literal("KEY_PGUP", ALLEGRO_KEY_PGUP, -3);
	Set_literal("KEY_PGDN", ALLEGRO_KEY_PGDN, -3);
	Set_literal("KEY_PAD_SLASH", ALLEGRO_KEY_PAD_SLASH, -3);
	Set_literal("KEY_PAD_ASTERISK", ALLEGRO_KEY_PAD_ASTERISK, -3);
	Set_literal("KEY_PAD_MINUS", ALLEGRO_KEY_PAD_MINUS, -3);
	Set_literal("KEY_PAD_PLUS", ALLEGRO_KEY_PAD_PLUS, -3);
	Set_literal("KEY_PAD_DELETE", ALLEGRO_KEY_PAD_DELETE, -3);
	Set_literal("KEY_PRINTSCREEN", ALLEGRO_KEY_PRINTSCREEN, -3);
	Set_literal("KEY_PAUSE", ALLEGRO_KEY_PAUSE, -3);
	Set_literal("KEY_ABNT_C1", ALLEGRO_KEY_ABNT_C1, -3);
	Set_literal("KEY_YEN", ALLEGRO_KEY_YEN, -3);
	Set_literal("KEY_KANA", ALLEGRO_KEY_KANA, -3);
	Set_literal("KEY_CONVERT", ALLEGRO_KEY_CONVERT, -3);
	Set_literal("KEY_NOCONVERT", ALLEGRO_KEY_NOCONVERT, -3);
	Set_literal("KEY_AT", ALLEGRO_KEY_AT, -3);
	Set_literal("KEY_CIRCUMFLEX", ALLEGRO_KEY_CIRCUMFLEX, -3);
	Set_literal("KEY_COLON2", ALLEGRO_KEY_COLON2, -3);
	Set_literal("KEY_KANJI", ALLEGRO_KEY_KANJI, -3);
	Set_literal("KEY_LSHIFT", ALLEGRO_KEY_LSHIFT, -3);
	Set_literal("KEY_RSHIFT", ALLEGRO_KEY_RSHIFT, -3);
	Set_literal("KEY_LCTRL", ALLEGRO_KEY_LCTRL, -3);
	Set_literal("KEY_RCTRL", ALLEGRO_KEY_RCTRL, -3);
	Set_literal("KEY_ALT", ALLEGRO_KEY_ALT, -3);
	Set_literal("KEY_ALTGR", ALLEGRO_KEY_ALTGR, -3);
	Set_literal("KEY_LWIN", ALLEGRO_KEY_LWIN, -3);
	Set_literal("KEY_RWIN", ALLEGRO_KEY_RWIN, -3);
	Set_literal("KEY_MENU", ALLEGRO_KEY_MENU, -3);
	Set_literal("KEY_SCROLLLOCK", ALLEGRO_KEY_SCROLLLOCK, -3);
	Set_literal("KEY_NUMLOCK", ALLEGRO_KEY_NUMLOCK, -3);
	Set_literal("KEY_CAPSLOCK", ALLEGRO_KEY_CAPSLOCK, -3);
	Set_literal("KEY_EQUALS_PAD", ALLEGRO_KEY_EQUALS_PAD, -3);
	Set_literal("KEY_BACKQUOTE", ALLEGRO_KEY_BACKQUOTE, -3);
	Set_literal("KEY_SEMICOLON2", ALLEGRO_KEY_SEMICOLON2, -3);
	Set_literal("KEY_COMMAND", ALLEGRO_KEY_COMMAND, -3);

	//Modifier flags
	Set_literal("KEYMOD_SHIFT", ALLEGRO_KEYMOD_SHIFT, -3);
	Set_literal("KEYMOD_CTRL", ALLEGRO_KEYMOD_CTRL, -3);
	Set_literal("KEYMOD_ALT", ALLEGRO_KEYMOD_ALT, -3);
	Set_literal("KEYMOD_LWIN", ALLEGRO_KEYMOD_LWIN, -3);
	Set_literal("KEYMOD_RWIN", ALLEGRO_KEYMOD_RWIN, -3);
	Set_literal("KEYMOD_MENU", ALLEGRO_KEYMOD_MENU, -3);
	Set_literal("KEYMOD_ALTGR", ALLEGRO_KEYMOD_ALTGR, -3);
	Set_literal("KEYMOD_COMMAND", ALLEGRO_KEYMOD_COMMAND, -3);
	Set_literal("KEYMOD_SCROLLLOCK", ALLEGRO_KEYMOD_SCROLLLOCK, -3);
	Set_literal("KEYMOD_NUMLOCK", ALLEGRO_KEYMOD_NUMLOCK, -3);
	Set_literal("KEYMOD_CAPSLOCK", ALLEGRO_KEYMOD_CAPSLOCK, -3);
	Set_literal("KEYMOD_INALTSEQ", ALLEGRO_KEYMOD_INALTSEQ, -3);
	Set_literal("KEYMOD_ACCENT1", ALLEGRO_KEYMOD_ACCENT1, -3);
	Set_literal("KEYMOD_ACCENT2", ALLEGRO_KEYMOD_ACCENT2, -3);
	Set_literal("KEYMOD_ACCENT3", ALLEGRO_KEYMOD_ACCENT3, -3);
	Set_literal("KEYMOD_ACCENT4", ALLEGRO_KEYMOD_ACCENT4, -3);
}

/* Register
 * */
int allua_register_keyboard (lua_State *L)
{
	allua_set_event_callback(ALLEGRO_EVENT_KEY_DOWN, allua_keyboard_event_callback);
	allua_set_event_callback(ALLEGRO_EVENT_KEY_REPEAT, allua_keyboard_event_callback);
	allua_set_event_callback(ALLEGRO_EVENT_KEY_UP, allua_keyboard_event_callback);

  lua_newtable(L);
  luaL_register(L, NULL, allua_Keyboard_methods);  /* create methods table,
                                                add it to the globals */

	allua_Keyboard_set_attributes(L);

  luaL_newmetatable(L, KEYBOARD_STRING);        /* create metatable for Image,
                                         add it to the Lua registry */
  luaL_register(L, 0, allua_Keyboard_meta);  /* fill metatable */
  lua_pushliteral(L, "__index");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* metatable.__index = methods */
  lua_pushliteral(L, "__metatable");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* hide metatable:
                                         metatable.__metatable = methods */
  lua_pop(L, 1);                      /* drop metatable */

  lua_setfield(L, -2, KEYBOARD_STRING);

  return 0;                           /* return methods on the stack */
}
