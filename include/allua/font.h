#ifndef allua_FONT_H
#define allua_FONT_H

#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>
#include <lua5.1/lauxlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>

typedef ALLEGRO_FONT* ALLUA_font;

/* Function: allua_register_font
 * Registers Font functionality to the lua state.
 * */
int allua_register_font (lua_State* L);

/* Function: allua_check_font
 * Returns:
 * Pointer to Font instance.
 * */
ALLUA_font allua_check_font (lua_State *L, int index);

#endif
