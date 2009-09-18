#ifndef allua_NATIVE_DIALOG_H
#define allua_NATIVE_DIALOG_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_native_dialog.h>

typedef ALLEGRO_NATIVE_DIALOG* ALLUA_native_dialog;

/* Function: allua_register_native_dialog
 * Registers Native_dialog functionality to the lua state.
 * */
int allua_register_native_dialog (lua_State* L);

/* Function: allua_check_native_dialog
 * Returns:
 * Pointer to Native_dialog instance.
 * */
ALLUA_native_dialog allua_check_native_dialog (lua_State *L, int index);

#endif
