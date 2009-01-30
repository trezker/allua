#ifndef AL_LUA_COLOR_H
#define AL_LUA_COLOR_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <allegro5/allegro5.h>

typedef ALLEGRO_COLOR AL_Color;

int al_lua_register_color (lua_State* L);

AL_Color al_lua_check_color (lua_State *L, int index);

#endif
