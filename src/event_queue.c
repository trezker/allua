#include "allua/event_queue.h"
#include "allua/display.h"
#include <stdio.h>

#define EVENT_QUEUE "Event_queue"

/* Common handlers
 * */
static AL_Event_queue toEvent_queue (lua_State *L, int index)
{
  AL_Event_queue *pi = (AL_Event_queue*)lua_touserdata(L, index);
  if (pi == NULL) luaL_typerror(L, index, EVENT_QUEUE);
  return *pi;
}

AL_Event_queue al_lua_check_event_queue (lua_State *L, int index)
{
  AL_Event_queue *pi, im;
  luaL_checktype(L, index, LUA_TUSERDATA);
  pi = (AL_Event_queue*)luaL_checkudata(L, index, EVENT_QUEUE);
  if (pi == NULL)
  	luaL_typerror(L, index, EVENT_QUEUE);
  im = *pi;
  if (!im)
    luaL_error(L, "null Event_queue");
  return im;
}

static AL_Event_queue *pushEvent_queue (lua_State *L, AL_Event_queue im)
{
  AL_Event_queue *pi = (AL_Event_queue *)lua_newuserdata(L, sizeof(AL_Event_queue));
  *pi = im;
  luaL_getmetatable(L, EVENT_QUEUE);
  lua_setmetatable(L, -2);
  return pi;
}

/* Constructor and methods
 * */
static int Event_queue_new (lua_State *L)
{
  pushEvent_queue(L, al_create_event_queue());

/*  AL_Event_queue event_queue = al_lua_check_event_queue(L, 1);
  printf("hello Event_queue (%p)\n", event_queue);
*/  return 1;
}

static int Event_queue_register_event_source (lua_State *L)
{
  AL_Event_queue event_queue = al_lua_check_event_queue(L, 1);

  ALLEGRO_EVENT_SOURCE** event_sourcep = (ALLEGRO_EVENT_SOURCE**)(lua_touserdata(L, 2));
  ALLEGRO_EVENT_SOURCE* event_source = *event_sourcep;
  if (!event_source)
  {
    luaL_error(L, "null Event_source");
  }
  al_register_event_source(event_queue, event_source);

  printf("Event_queue (%p) ", event_queue);
  printf("registered (%p)\n", event_source);
  return 0;
}

static int Event_queue_unregister_event_source (lua_State *L)
{
  AL_Event_queue event_queue = al_lua_check_event_queue(L, 1);

  ALLEGRO_EVENT_SOURCE** event_sourcep = (ALLEGRO_EVENT_SOURCE**)(lua_touserdata(L, 2));
  ALLEGRO_EVENT_SOURCE* event_source = *event_sourcep;
  if (!event_source)
  {
    luaL_error(L, "null Event_source");
  }
  al_unregister_event_source(event_queue, event_source);

  printf("Event_queue (%p) ", event_queue);
  printf("unregistered (%p)\n", event_source);
  return 0;
}

struct Event_callback
{
	ALLEGRO_EVENT_TYPE event;
	void (*cb) (lua_State *L, ALLEGRO_EVENT *e);
}event_callbacks[29];

//Event_callback ;
int num_event_callbacks = 0;

void al_lua_set_event_callback(ALLEGRO_EVENT_TYPE event, void (*cb) (lua_State *L, ALLEGRO_EVENT *e))
{
	event_callbacks[num_event_callbacks].event = event;
	event_callbacks[num_event_callbacks].cb = cb;
	++num_event_callbacks;
}

static int Event_queue_get_next_event (lua_State *L)
{
  AL_Event_queue event_queue = al_lua_check_event_queue(L, 1);

	lua_newtable (L);

	ALLEGRO_EVENT event;
	if (al_get_next_event(event_queue, &event))
	{
		lua_pushstring(L, "type");
		lua_pushinteger(L, event.type);
		lua_settable(L, -3);
		
		/* Each type of event source may have different data in the event
		 * This lookup calls a handler that fills in that data
		 * */
		int i = 0;
		for(; i<num_event_callbacks; ++i)
		{
			if(event_callbacks[i].event == event.type)
			{
				event_callbacks[i].cb(L, &event);
				break;
			}
		}
	}
	return 1;
}

static const luaL_reg Event_queue_methods[] = {
  {"new",           Event_queue_new},
  {"register_event_source",           Event_queue_register_event_source},
  {"unregister_event_source",           Event_queue_unregister_event_source},
  {"get_next_event",           Event_queue_get_next_event},
  {0,0}
};

/* GC and meta
 * */
static int Event_queue_gc (lua_State *L)
{
  AL_Event_queue im = toEvent_queue(L, 1);
  printf("goodbye Event_queue (%p)\n", im);
  if (im) al_destroy_event_queue(im);
  return 0;
}

static int Event_queue_tostring (lua_State *L)
{
  lua_pushfstring(L, "Event_queue: %p", lua_touserdata(L, 1));
  return 1;
}

static const luaL_reg Event_queue_meta[] = {
  {"__gc",       Event_queue_gc},
  {"__tostring", Event_queue_tostring},
  {0, 0}
};

/* Register
 * */
int al_lua_register_event_queue (lua_State *L)
{
  lua_newtable(L);
  luaL_register(L, NULL, Event_queue_methods);  /* create methods table,
                                                add it to the globals */
  luaL_newmetatable(L, EVENT_QUEUE);        /* create metatable for Image,
                                         add it to the Lua registry */
  luaL_register(L, 0, Event_queue_meta);  /* fill metatable */
  lua_pushliteral(L, "__index");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* metatable.__index = methods */
  lua_pushliteral(L, "__metatable");
  lua_pushvalue(L, -3);               /* dup methods table*/
  lua_rawset(L, -3);                  /* hide metatable:
                                         metatable.__metatable = methods */
  lua_pop(L, 1);                      /* drop metatable */
  
  lua_setfield(L, -2, EVENT_QUEUE);
  return 0;                           /* return methods on the stack */
}

