#include "allua/keyboard.h"
#include "allua/event_queue.h"
#include "allua/al_lua.h"
#include <stdio.h>

#define KEYBOARD "Keyboard"

/* Common handlers
 * */
/*static AL_Keyboard toKeyboard (lua_State *L, int index)
{
  AL_Keyboard *pi = (AL_Keyboard*)lua_touserdata(L, index);
  if (pi == NULL) luaL_typerror(L, index, KEYBOARD);
  return *pi;
}
*/
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

static int al_lua_keycode_from_name(lua_State *L)
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

static const luaL_reg Keyboard_methods[] = {
  {"get",           al_lua_get_keyboard},
  {"keycode_to_name",           al_lua_keycode_to_name},
  {"keycode_from_name",           al_lua_keycode_from_name},
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
	Set_literal("ALLEGRO_KEY_ABNT_C1", ALLEGRO_KEY_ABNT_C1, -3);
	Set_literal("ALLEGRO_KEY_YEN", ALLEGRO_KEY_YEN, -3);
	Set_literal("ALLEGRO_KEY_KANA", ALLEGRO_KEY_KANA, -3);
	Set_literal("ALLEGRO_KEY_CONVERT", ALLEGRO_KEY_CONVERT, -3);
	Set_literal("ALLEGRO_KEY_NOCONVERT", ALLEGRO_KEY_NOCONVERT, -3);
	Set_literal("ALLEGRO_KEY_AT", ALLEGRO_KEY_AT, -3);
	Set_literal("ALLEGRO_KEY_CIRCUMFLEX", ALLEGRO_KEY_CIRCUMFLEX, -3);
	Set_literal("ALLEGRO_KEY_COLON2", ALLEGRO_KEY_COLON2, -3);
	Set_literal("ALLEGRO_KEY_KANJI", ALLEGRO_KEY_KANJI, -3);
	Set_literal("ALLEGRO_KEY_LSHIFT", ALLEGRO_KEY_LSHIFT, -3);
	Set_literal("ALLEGRO_KEY_RSHIFT", ALLEGRO_KEY_RSHIFT, -3);
	Set_literal("ALLEGRO_KEY_LCTRL", ALLEGRO_KEY_LCTRL, -3);
	Set_literal("ALLEGRO_KEY_RCTRL", ALLEGRO_KEY_RCTRL, -3);
	Set_literal("ALLEGRO_KEY_ALT", ALLEGRO_KEY_ALT, -3);
	Set_literal("ALLEGRO_KEY_ALTGR", ALLEGRO_KEY_ALTGR, -3);
	Set_literal("ALLEGRO_KEY_LWIN", ALLEGRO_KEY_LWIN, -3);
	Set_literal("ALLEGRO_KEY_RWIN", ALLEGRO_KEY_RWIN, -3);
	Set_literal("ALLEGRO_KEY_MENU", ALLEGRO_KEY_MENU, -3);
	Set_literal("ALLEGRO_KEY_SCROLLLOCK", ALLEGRO_KEY_SCROLLLOCK, -3);
	Set_literal("ALLEGRO_KEY_NUMLOCK", ALLEGRO_KEY_NUMLOCK, -3);
	Set_literal("ALLEGRO_KEY_CAPSLOCK", ALLEGRO_KEY_CAPSLOCK, -3);
	Set_literal("ALLEGRO_KEY_EQUALS_PAD", ALLEGRO_KEY_EQUALS_PAD, -3);
	Set_literal("ALLEGRO_KEY_BACKQUOTE", ALLEGRO_KEY_BACKQUOTE, -3);
	Set_literal("ALLEGRO_KEY_SEMICOLON2", ALLEGRO_KEY_SEMICOLON2, -3);
	Set_literal("ALLEGRO_KEY_COMMAND", ALLEGRO_KEY_COMMAND, -3);
}

/* Register
 * */
int al_lua_register_keyboard (lua_State *L)
{
	al_lua_set_event_callback(ALLEGRO_EVENT_KEY_DOWN, al_lua_keyboard_event_callback);
	al_lua_set_event_callback(ALLEGRO_EVENT_KEY_REPEAT, al_lua_keyboard_event_callback);
	al_lua_set_event_callback(ALLEGRO_EVENT_KEY_UP, al_lua_keyboard_event_callback);

  lua_newtable(L);
  luaL_register(L, NULL, Keyboard_methods);  /* create methods table,
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

  lua_setfield(L, -2, KEYBOARD);

  return 0;                           /* return methods on the stack */
}
