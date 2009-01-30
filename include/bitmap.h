#ifndef AL_LUA_BITMAP_H
#define AL_LUA_BITMAP_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <allegro5/allegro5.h>

typedef ALLEGRO_BITMAP* AL_Bitmap;

int al_lua_register_bitmap (lua_State* L);

AL_Bitmap al_lua_check_bitmap (lua_State *L, int index);

#endif
