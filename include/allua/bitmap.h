#ifndef AL_LUA_BITMAP_H
#define AL_LUA_BITMAP_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <allegro5/allegro5.h>

typedef ALLEGRO_BITMAP* AL_Bitmap;

struct AL_Bitmap_s
{
	ALLEGRO_BITMAP* bitmap;
	int gc_allowed;
};

/* Function: al_lua_register_bitmap
 * Registers Bitmap functionality to the lua state.
 * */
int al_lua_register_bitmap (lua_State* L);

/* Function: al_lua_check_bitmap
 * Returns:
 * Pointer to Bitmap instance.
 * */
AL_Bitmap al_lua_check_bitmap (lua_State *L, int index);//, int *gc_allowed);
struct AL_Bitmap_s *pushBitmap (lua_State *L, AL_Bitmap im, int gc_allowed);

#endif
