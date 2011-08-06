#include "../include/allua/allua.h"
#include "../include/allua/display.h"
#include "../include/allua/event.h"
#include "../include/allua/event_queue.h"
#include "../include/allua/event_source.h"
#include "../include/allua/color.h"
#include "../include/allua/keyboard.h"
#include "../include/allua/mouse.h"
#include "../include/allua/bitmap.h"
#include "../include/allua/font.h"
#include "../include/allua/filesystem.h"
#include "../include/allua/fs_entry.h"
#include "../include/allua/path.h"
#include "../include/allua/primitives.h"
#include "../include/allua/audio.h"
#include "../include/allua/voice.h"
#include "../include/allua/mixer.h"
#include "../include/allua/sample.h"
#include "../include/allua/sample_id.h"
#include "../include/allua/sample_instance.h"
#include "../include/allua/audio_stream.h"
#include "../include/allua/filechooser.h"
#include <stdio.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

int luaopen_liballua(lua_State * L)
{
   allua_register(L);
   return 0;
}

/* Init
 * */
static int allua_init(lua_State * L)
{
   printf("Initialized allegro\n");
   al_init();
   return 0;
}

static int allua_current_time(lua_State * L)
{
   lua_pushnumber(L, al_current_time());
   return 1;
}


static int allua_rest(lua_State * L)
{
   float t = luaL_checknumber(L, 1);
   al_rest(t);
   return 0;
}

/* Register
 * */
static const luaL_reg allua_lib[] = {
   {"init", allua_init},
   {"current_time", allua_current_time},
   {"rest", allua_rest},
   {NULL, NULL}
};

int allua_register(lua_State * L)
{
   /* Initialize weak udata mapping table, weak on the udata */
   lua_newtable(L);
   lua_newtable(L);
   lua_pushliteral(L, "v");
   lua_setfield(L, -2, "__mode");
   lua_setmetatable(L, -2);
   lua_setfield(L, LUA_REGISTRYINDEX, "allegro5udatamap");

   /* Register everything */
   luaL_register(L, "allegro5", allua_lib);
   allua_register_font(L);
   allua_register_bitmap(L);
   allua_register_filesystem(L);
   allua_register_fs_entry(L);
   allua_register_path(L);
   allua_register_keyboard(L);
   allua_register_mouse(L);
   allua_register_display(L);
   allua_register_event(L);
   allua_register_event_queue(L);
   allua_register_event_source(L);
   allua_register_color(L);
   allua_register_primitives(L);
   allua_register_audio(L);
   allua_register_voice(L);
   allua_register_mixer(L);
   allua_register_sample(L);
   allua_register_sample_id(L);
   allua_register_sample_instance(L);
   allua_register_audio_stream(L);
   allua_register_filechooser(L);
   lua_pop(L, 1);
   return 1;
}

/* vim: set sts=3 sw=3 et: */
