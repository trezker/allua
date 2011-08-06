#include "../include/allua/voice.h"
#include <stdio.h>

#define VOICE_STRING "voice"

/* Common handlers
 * */
/*static ALLUA_voice tovoice (lua_State *L, int index)//, int *gc_allowed)
{
  struct ALLUA_voice_s *pi = (struct ALLUA_voice_s*)lua_touserdata(L, index);
  if (pi == NULL) luaL_typerror(L, index, VOICE_STRING);
//  if(gc_allowed)
//  	*gc_allowed = pi->gc_allowed;
  return pi->voice;
}
*/
ALLUA_voice allua_check_voice(lua_State * L, int index /* int *gc_allowed */ )
{
   struct ALLUA_voice_s *pi;
   ALLUA_voice im;
   luaL_checktype(L, index, LUA_TUSERDATA);
   pi = (struct ALLUA_voice_s *)luaL_checkudata(L, index, VOICE_STRING);
   if (pi == NULL)
      luaL_typerror(L, index, VOICE_STRING);
   im = pi->voice;
   if (!im)
      luaL_error(L, "null voice");
   return im;
}

struct ALLUA_voice_s *allua_pushvoice(lua_State * L, ALLUA_voice im,
                                      int gc_allowed)
{
   struct ALLUA_voice_s *pi;
   if (!im) {
      lua_pushnil(L);
      return NULL;
   }
   pi = (struct ALLUA_voice_s *)lua_newuserdata(L,
                                                sizeof(struct ALLUA_voice_s));
   pi->voice = im;
   pi->gc_allowed = gc_allowed;
   luaL_getmetatable(L, VOICE_STRING);
   lua_setmetatable(L, -2);
   return pi;
}

/* Constructor and methods
 * */

static int allua_voice_create(lua_State * L)
{
   int freq = luaL_checkint(L, 1);
   int depth = luaL_checkint(L, 2);
   int chan_conf = luaL_checkint(L, 3);

   ALLUA_voice voice = al_create_voice(freq, depth, chan_conf);
   if (voice)
      allua_pushvoice(L, voice, true);
   else
      lua_pushnil(L);
   return 1;
}

static const luaL_reg allua_voice_methods[] = {
   {"create", allua_voice_create},
   {0, 0}
};

/* GC and meta
 * */
static int allua_voice_gc(lua_State * L)
{
   struct ALLUA_voice_s *pi = (struct ALLUA_voice_s *)lua_touserdata(L, 1);
   if (pi->gc_allowed) {
      ALLUA_voice im = pi->voice;
      printf("goodbye voice (%p)\n", (void *)im);
      if (im)
         al_destroy_voice(im);
   }
   return 0;
}

static int allua_voice_tostring(lua_State * L)
{
   lua_pushfstring(L, "voice: %p", lua_touserdata(L, 1));
   return 1;
}

static const luaL_reg allua_voice_meta[] = {
   {"__gc", allua_voice_gc},
   {"__tostring", allua_voice_tostring},
   {0, 0}
};

/* Other attributes
 * */
void allua_voice_set_attributes(lua_State * L)
{
}

/* Register
 * */
int allua_register_voice(lua_State * L)
{
   lua_newtable(L);
   luaL_register(L, NULL, allua_voice_methods); /* create methods table,
                                                   add it to the globals */

   allua_voice_set_attributes(L);

   luaL_newmetatable(L, VOICE_STRING);  /* create metatable for Image,
                                           add it to the Lua registry */
   luaL_register(L, 0, allua_voice_meta);       /* fill metatable */
   lua_pushliteral(L, "__index");
   lua_pushvalue(L, -3);        /* dup methods table */
   lua_rawset(L, -3);           /* metatable.__index = methods */
   lua_pushliteral(L, "__metatable");
   lua_pushvalue(L, -3);        /* dup methods table */
   lua_rawset(L, -3);           /* hide metatable:
                                   metatable.__metatable = methods */
   lua_pop(L, 1);               /* drop metatable */

   lua_setfield(L, -2, VOICE_STRING);

   return 0;                    /* return methods on the stack */
}

/* vim: set sts=3 sw=3 et: */
