#include "allua/al_lua.h"
#include "allua/display.h"
#include "allua/event_queue.h"
#include "allua/color.h"
#include "allua/keyboard.h"
#include "allua/mouse.h"
#include "allua/bitmap.h"
#include "allua/font.h"
#include "allua/primitives.h"
#include <stdio.h>

#include <allegro5/allegro5.h>
#include <allegro5/a5_ttf.h>
#include <allegro5/a5_iio.h>

/* Init
 * */
static int al_lua_init(lua_State *L)
{
	printf("Initialized allegro\n");
	al_init();
	al_install_keyboard();
	al_install_mouse();
	al_init_iio_addon();
	al_init_font_addon();
	return 0;
}

static int al_lua_current_time(lua_State *L)
{
	lua_pushnumber(L, al_current_time());
	return 1;
}


static int al_lua_rest(lua_State *L)
{
	float t = luaL_checknumber(L, 1);
	al_rest(t);
	return 0;
}

/* Register
 * */
static const luaL_reg al_lua_lib[] = {
  {"init", al_lua_init},
  {"current_time", al_lua_current_time},
  {"rest", al_lua_rest},
  {NULL, NULL}
};

int al_lua_register(lua_State *L)
{
//    lua_pushlightuserdata(L, (void *)&Key);  /* push address */
//    lua_pushnumber(L, myNumber);  /* push value */
    /* registry[&Key] = myNumber */
//    lua_settable(L, LUA_REGISTRYINDEX);
    /* retrieve a number */
//    lua_pushlightuserdata(L, (void *)&Key);  /* push address */
//    lua_gettable(L, LUA_REGISTRYINDEX);  /* retrieve value */
//    myNumber = lua_tonumber(L, -1);  /* convert to number */

	/* Initialize weak udata mapping table, weak on the udata */
	lua_newtable (L);
	lua_pushliteral(L, "v");
    lua_setfield(L, -2, "__mode");
    lua_setfield(L, LUA_REGISTRYINDEX, "allegro5udatamap");






	luaL_register (L, "allegro5", al_lua_lib);
	al_lua_register_font(L);
	al_lua_register_bitmap(L);
	al_lua_register_keyboard(L);
	al_lua_register_mouse(L);
	al_lua_register_display(L);
	al_lua_register_event_queue(L);
	al_lua_register_color(L);
	al_lua_register_primitives(L);
	lua_pop(L, 1);
	return 1;
}
