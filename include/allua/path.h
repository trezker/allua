#ifndef allua_PATH_H
#define allua_PATH_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <allegro5/allegro5.h>

typedef ALLEGRO_PATH *ALLUA_path;

struct ALLUA_path_s
{
   ALLEGRO_PATH *path;
   int gc_allowed;
};

/* Function: allua_register_path
 * Registers Path functionality to the lua state.
 * */
int allua_register_path(lua_State * L);

/* Function: allua_check_path
 * Returns:
 * Pointer to Path instance.
 * */
ALLUA_path allua_check_path(lua_State * L, int index /* int *gc_allowed */ );
struct ALLUA_path_s *allua_pushPath(lua_State * L, ALLUA_path im,
                                    int gc_allowed);

/* vim: set sts=3 sw=3 et: */
#endif
