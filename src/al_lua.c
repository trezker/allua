#include "al_lua.h"
#include "display.h"
#include "event_queue.h"
#include "color.h"
#include "keyboard.h"
#include "bitmap.h"
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
	al_iio_init();
	al_font_init();
	return 0;
}

static int al_lua_current_time(lua_State *L)
{
	lua_pushnumber(L, al_current_time());
	return 1;
}

/* Register
 * */
static const luaL_reg al_lua_lib[] = {
  {"init", al_lua_init},
  {"current_time", al_lua_current_time},
  {NULL, NULL}
};

int al_lua_register(lua_State *L)
{
	luaL_register (L, "allegro5", al_lua_lib);
	lua_pop(L, 1);
	al_lua_register_display(L);
	al_lua_register_event_queue(L);
	al_lua_register_color(L);
	al_lua_register_keyboard(L);
	al_lua_register_bitmap(L);
	return 1;
}
