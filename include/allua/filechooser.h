#ifndef allua_FILECHOOSER_H
#define allua_FILECHOOSER_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_native_dialog.h>

typedef ALLEGRO_FILECHOOSER* ALLUA_filechooser;

/* Function: allua_register_filechooser
 * Registers Filechooser functionality to the lua state.
 * */
int allua_register_filechooser (lua_State* L);

/* Function: allua_check_filechooser
 * Returns:
 * Pointer to Filechooser instance.
 * */
ALLUA_filechooser allua_check_filechooser (lua_State *L, int index);

#endif
