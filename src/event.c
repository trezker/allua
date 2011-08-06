#include "../include/allua/event.h"
#include <stdio.h>

#define EVENT_STRING "event"

/* Common handlers
 * */
ALLEGRO_EVENT allua_check_event(lua_State * L, int index)
{
   ALLEGRO_EVENT *pi, im;
   luaL_checktype(L, index, LUA_TUSERDATA);
   pi = (ALLEGRO_EVENT *) luaL_checkudata(L, index, EVENT_STRING);
   if (pi == NULL)
      luaL_typerror(L, index, EVENT_STRING);
   im = *pi;
   return im;
}

ALLEGRO_EVENT *allua_pushEvent(lua_State * L, ALLEGRO_EVENT im)
{
   ALLEGRO_EVENT *pi =
       (ALLEGRO_EVENT *) lua_newuserdata(L, sizeof(ALLEGRO_EVENT));
   *pi = im;
   luaL_getmetatable(L, EVENT_STRING);
   lua_setmetatable(L, -2);
   return pi;
}

/* Constructor and methods
 * */

static const luaL_reg allua_Event_methods[] = {
   {0, 0}
};

/* GC and meta
 * */
static int allua_Event_tostring(lua_State * L)
{
   lua_pushfstring(L, "event: %p", lua_touserdata(L, 1));
   return 1;
}

static const luaL_reg allua_Event_meta[] = {
   {"__tostring", allua_Event_tostring},
   {0, 0}
};

/* Register
 * */
int allua_register_event(lua_State * L)
{
   lua_newtable(L);
   luaL_register(L, NULL, allua_Event_methods); /* create methods table,
                                                   add it to the globals */
   luaL_newmetatable(L, EVENT_STRING);  /* create metatable for Image,
                                           add it to the Lua registry */
   luaL_register(L, 0, allua_Event_meta);       /* fill metatable */
   lua_pushliteral(L, "__index");
   lua_pushvalue(L, -3);        /* dup methods table */
   lua_rawset(L, -3);           /* metatable.__index = methods */
   lua_pushliteral(L, "__metatable");
   lua_pushvalue(L, -3);        /* dup methods table */
   lua_rawset(L, -3);           /* hide metatable:
                                   metatable.__metatable = methods */
   lua_pop(L, 1);               /* drop metatable */

   lua_setfield(L, -2, EVENT_STRING);
   return 0;                    /* return methods on the stack */
}

/* vim: set sts=3 sw=3 et: */
