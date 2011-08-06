#include "../include/allua/event_queue.h"
#include "../include/allua/event_source.h"
#include "../include/allua/event.h"
#include <stdio.h>

#define EVENT_QUEUE_STRING "event_queue"

/* Common handlers
 * */
static ALLUA_event_queue allua_toEvent_queue(lua_State * L, int index)
{
   ALLUA_event_queue *pi = (ALLUA_event_queue *) lua_touserdata(L, index);
   if (pi == NULL)
      luaL_typerror(L, index, EVENT_QUEUE_STRING);
   return *pi;
}

ALLUA_event_queue allua_check_event_queue(lua_State * L, int index)
{
   ALLUA_event_queue *pi, im;
   luaL_checktype(L, index, LUA_TUSERDATA);
   pi = (ALLUA_event_queue *) luaL_checkudata(L, index, EVENT_QUEUE_STRING);
   if (pi == NULL)
      luaL_typerror(L, index, EVENT_QUEUE_STRING);
   im = *pi;
   if (!im)
      luaL_error(L, "null Event_queue");
   return im;
}

static ALLUA_event_queue *allua_pushEvent_queue(lua_State * L,
                                                ALLUA_event_queue im)
{
   ALLUA_event_queue *pi;
   if (!im) {
      lua_pushnil(L);
      return NULL;
   }
   pi = (ALLUA_event_queue *) lua_newuserdata(L, sizeof(ALLUA_event_queue));
   *pi = im;
   luaL_getmetatable(L, EVENT_QUEUE_STRING);
   lua_setmetatable(L, -2);
   return pi;
}

/* Constructor and methods
 * */
static int allua_Event_queue_create(lua_State * L)
{
   allua_pushEvent_queue(L, al_create_event_queue());
   return 1;
}

static int allua_Event_queue_register_event_source(lua_State * L)
{
   ALLUA_event_queue event_queue = allua_check_event_queue(L, 1);

   ALLUA_event_source event_source = allua_check_event_source(L, 2);
   if (!event_source) {
      luaL_error(L, "null Event_source");
   }
   al_register_event_source(event_queue, event_source);

   printf("Event_queue (%p) ", (void *)event_queue);
   printf("registered (%p)\n", (void *)event_source);
   return 0;
}

static int allua_Event_queue_unregister_event_source(lua_State * L)
{
   ALLUA_event_queue event_queue = allua_check_event_queue(L, 1);

   ALLUA_event_source event_source = allua_check_event_source(L, 2);
   if (!event_source) {
      luaL_error(L, "null Event_source");
   }
   al_unregister_event_source(event_queue, event_source);

   printf("Event_queue (%p) ", (void *)event_queue);
   printf("unregistered (%p)\n", (void *)event_source);
   return 0;
}

struct allua_Event_callback
{
   ALLEGRO_EVENT_TYPE event;
   void (*cb) (lua_State * L, ALLEGRO_EVENT * e);
} event_callbacks[29];

/* event_callback */
int num_event_callbacks = 0;

void allua_set_event_callback(ALLEGRO_EVENT_TYPE event,
                              void (*cb) (lua_State * L, ALLEGRO_EVENT * e))
{
   event_callbacks[num_event_callbacks].event = event;
   event_callbacks[num_event_callbacks].cb = cb;
   ++num_event_callbacks;
}

/* TODO: Make event userdata and add as a field.
 * This is so that the event can be given back to C/C++.
 * */
static int allua_Event_queue_get_event_common(lua_State * L, bool got_event,
                                              ALLEGRO_EVENT * event)
{
   lua_newtable(L);
   if (got_event) {
      int i;

      lua_pushstring(L, "type");
      lua_pushinteger(L, event->type);
      lua_settable(L, -3);

      lua_pushstring(L, "cevent");
      allua_pushEvent(L, *event);
      lua_settable(L, -3);

      /* Each type of event source may have different data in the event
       * This lookup calls a handler that fills in that data
       * */
      for (i = 0; i < num_event_callbacks; ++i) {
         if (event_callbacks[i].event == event->type) {
            event_callbacks[i].cb(L, event);
            break;
         }
      }
   }
   return 1;
}

static int allua_Event_queue_get_next_event(lua_State * L)
{
   ALLUA_event_queue event_queue = allua_check_event_queue(L, 1);
   ALLEGRO_EVENT event;
   bool got_event = al_get_next_event(event_queue, &event);
   return allua_Event_queue_get_event_common(L, got_event, &event);
}

static int allua_Event_queue_peek_next_event(lua_State * L)
{
   ALLUA_event_queue event_queue = allua_check_event_queue(L, 1);
   ALLEGRO_EVENT event;
   bool got_event = al_peek_next_event(event_queue, &event);
   return allua_Event_queue_get_event_common(L, got_event, &event);
}

static int allua_Event_queue_wait_for_event(lua_State * L)
{
   ALLUA_event_queue event_queue = allua_check_event_queue(L, 1);
   ALLEGRO_EVENT event;
   al_wait_for_event(event_queue, &event);
   return allua_Event_queue_get_event_common(L, true, &event);
}

static int allua_Event_queue_wait_for_event_timed(lua_State * L)
{
   ALLUA_event_queue event_queue = allua_check_event_queue(L, 1);
   float secs = luaL_checknumber(L, 2);
   ALLEGRO_EVENT event;
   bool got_event = al_wait_for_event_timed(event_queue, &event, secs);
   return allua_Event_queue_get_event_common(L, got_event, &event);
}

static int allua_Event_queue_drop_next_event(lua_State * L)
{
   ALLUA_event_queue event_queue = allua_check_event_queue(L, 1);
   lua_pushboolean(L, al_drop_next_event(event_queue));
   return 1;
}

static int allua_Event_queue_is_empty(lua_State * L)
{
   ALLUA_event_queue event_queue = allua_check_event_queue(L, 1);
   lua_pushboolean(L, al_event_queue_is_empty(event_queue));
   return 1;
}

static int allua_Event_queue_flush(lua_State * L)
{
   ALLUA_event_queue event_queue = allua_check_event_queue(L, 1);
   al_flush_event_queue(event_queue);
   return 0;
}

static const luaL_reg allua_Event_queue_methods[] = {
   {"create", allua_Event_queue_create},
   {"drop_next_event", allua_Event_queue_drop_next_event},
   {"is_empty", allua_Event_queue_is_empty},
   {"flush", allua_Event_queue_flush},
   {"get_next_event", allua_Event_queue_get_next_event},
   {"peek_next_event", allua_Event_queue_peek_next_event},
   {"wait_for_event", allua_Event_queue_wait_for_event},
   {"wait_for_event_timed", allua_Event_queue_wait_for_event_timed},
   {"register_event_source", allua_Event_queue_register_event_source},
   {"unregister_event_source", allua_Event_queue_unregister_event_source},
   {0, 0}
};

/* GC and meta
 * */
static int allua_Event_queue_gc(lua_State * L)
{
   ALLUA_event_queue im = allua_toEvent_queue(L, 1);
   printf("goodbye Event_queue (%p)\n", (void *)im);
   if (im)
      al_destroy_event_queue(im);
   return 0;
}

static int allua_Event_queue_tostring(lua_State * L)
{
   lua_pushfstring(L, "event_queue: %p", lua_touserdata(L, 1));
   return 1;
}

static const luaL_reg allua_Event_queue_meta[] = {
   {"__gc", allua_Event_queue_gc},
   {"__tostring", allua_Event_queue_tostring},
   {0, 0}
};

/* Register
 * */
int allua_register_event_queue(lua_State * L)
{
   lua_newtable(L);
   luaL_register(L, NULL, allua_Event_queue_methods);   /* create methods table,
                                                           add it to the globals */
   luaL_newmetatable(L, EVENT_QUEUE_STRING);    /* create metatable for Image,
                                                   add it to the Lua registry */
   luaL_register(L, 0, allua_Event_queue_meta); /* fill metatable */
   lua_pushliteral(L, "__index");
   lua_pushvalue(L, -3);        /* dup methods table */
   lua_rawset(L, -3);           /* metatable.__index = methods */
   lua_pushliteral(L, "__metatable");
   lua_pushvalue(L, -3);        /* dup methods table */
   lua_rawset(L, -3);           /* hide metatable:
                                   metatable.__metatable = methods */
   lua_pop(L, 1);               /* drop metatable */

   lua_setfield(L, -2, EVENT_QUEUE_STRING);
   return 0;                    /* return methods on the stack */
}

/* vim: set sts=3 sw=3 et: */
