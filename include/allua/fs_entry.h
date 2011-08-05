#ifndef allua_FS_ENTRY_H
#define allua_FS_ENTRY_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <allegro5/allegro5.h>

typedef ALLEGRO_FS_ENTRY *ALLUA_fs_entry;

struct ALLUA_fs_entry_s
{
   ALLEGRO_FS_ENTRY *fs_entry;
   int gc_allowed;
};

/* Function: allua_register_fs_entry
 * Registers Fs_entry functionality to the lua state.
 * */
int allua_register_fs_entry(lua_State * L);

/* Function: allua_check_fs_entry
 * Returns:
 * Pointer to Fs_entry instance.
 * */
ALLUA_fs_entry allua_check_fs_entry(lua_State * L,
                                    int index /* int *gc_allowed */ );
struct ALLUA_fs_entry_s *allua_pushFs_entry(lua_State * L, ALLUA_fs_entry im,
                                            int gc_allowed);

#endif
