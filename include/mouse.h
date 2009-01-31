#ifndef AL_LUA_MOUSE_H
#define AL_LUA_MOUSE_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <allegro5/allegro5.h>

typedef ALLEGRO_MOUSE* AL_Mouse;

int al_lua_register_mouse (lua_State* L);

AL_Mouse al_lua_check_mouse (lua_State *L, int index);

#endif
