#include "../include/allua/event_source.h"
#include <stdio.h>

#define EVENT_SOURCE_STRING "event_source"

/* Common handlers
 * */
/*static ALLUA_event_source toevent_source (lua_State *L, int index)//, int *gc_allowed)
{
  struct ALLUA_event_source_s *pi = (struct ALLUA_event_source_s*)lua_touserdata(L, index);
  if (pi == NULL) luaL_typerror(L, index, EVENT_SOURCE_STRING);
//  if(gc_allowed)
//  	*gc_allowed = pi->gc_allowed;
  return pi->event_source;
}
*/
ALLUA_event_source allua_check_event_source(lua_State * L, int index)
{
   ALLUA_event_source *pi;
   ALLUA_event_source im;
   luaL_checktype(L, index, LUA_TUSERDATA);
   pi = (ALLUA_event_source *) luaL_checkudata(L, index, EVENT_SOURCE_STRING);
   if (pi == NULL)
      luaL_typerror(L, index, EVENT_SOURCE_STRING);
   im = *pi;
   if (!im)
      luaL_error(L, "null event_source");
   return im;
}

ALLUA_event_source *allua_pushevent_source(lua_State * L, ALLUA_event_source im)
{
   ALLUA_event_source *pi;
   if (!im) {
      lua_pushnil(L);
      return NULL;
   }

   pi = (ALLUA_event_source *) lua_newuserdata(L, sizeof(ALLUA_event_source));
   *pi = im;
   luaL_getmetatable(L, EVENT_SOURCE_STRING);
   lua_setmetatable(L, -2);
   return pi;
}

/* Constructor and methods
 * */

static const luaL_reg allua_event_source_methods[] = {
   {0, 0}
};

/* GC and meta
 * */

static int allua_event_source_tostring(lua_State * L)
{
   lua_pushfstring(L, "event_source: %p", lua_touserdata(L, 1));
   return 1;
}

static const luaL_reg allua_event_source_meta[] = {
   {"__tostring", allua_event_source_tostring},
   {0, 0}
};

/* Other attributes
 * */
void allua_event_source_set_attributes(lua_State * L)
{
}

/* Register
 * */
int allua_register_event_source(lua_State * L)
{
   lua_newtable(L);
   luaL_register(L, NULL, allua_event_source_methods);  /* create methods table,
                                                           add it to the globals */

   allua_event_source_set_attributes(L);

   luaL_newmetatable(L, EVENT_SOURCE_STRING);   /* create metatable for Image,
                                                   add it to the Lua registry */
   luaL_register(L, 0, allua_event_source_meta);        /* fill metatable */
   lua_pushliteral(L, "__index");
   lua_pushvalue(L, -3);        /* dup methods table */
   lua_rawset(L, -3);           /* metatable.__index = methods */
   lua_pushliteral(L, "__metatable");
   lua_pushvalue(L, -3);        /* dup methods table */
   lua_rawset(L, -3);           /* hide metatable:
                                   metatable.__metatable = methods */
   lua_pop(L, 1);               /* drop metatable */

   lua_setfield(L, -2, EVENT_SOURCE_STRING);

   return 0;                    /* return methods on the stack */
}
