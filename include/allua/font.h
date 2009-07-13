#ifndef allua_FONT_H
#define allua_FONT_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/a5_ttf.h>

typedef ALLEGRO_FONT* AL_font;

/* Function: allua_register_font
 * Registers Font functionality to the lua state.
 * */
int allua_register_font (lua_State* L);

/* Function: allua_check_font
 * Returns:
 * Pointer to Font instance.
 * */
AL_font allua_check_font (lua_State *L, int index);

#endif
