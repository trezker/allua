#ifndef AL_LUA_FONT_H
#define AL_LUA_FONT_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/a5_ttf.h>

typedef ALLEGRO_FONT* AL_Font;

int al_lua_register_font (lua_State* L);

AL_Font al_lua_check_font (lua_State *L, int index);

#endif
