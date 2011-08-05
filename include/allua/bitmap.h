#ifndef allua_BITMAP_H
#define allua_BITMAP_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <allegro5/allegro5.h>

typedef ALLEGRO_BITMAP* ALLUA_bitmap;

struct ALLUA_bitmap_s
{
	ALLEGRO_BITMAP* bitmap;
	int gc_allowed;
};

/* Function: allua_register_bitmap
 * Registers Bitmap functionality to the lua state.
 * */
int allua_register_bitmap (lua_State* L);

/* Function: allua_check_bitmap
 * Returns:
 * Pointer to Bitmap instance.
 * */
ALLUA_bitmap allua_check_bitmap (lua_State *L, int index);//, int *gc_allowed);
struct ALLUA_bitmap_s *allua_pushBitmap (lua_State *L, ALLUA_bitmap im, int gc_allowed);

#endif
