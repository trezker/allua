#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <allegro5/allegro5.h>

typedef ALLEGRO_EVENT_QUEUE* AL_Event_queue;

/* Function: al_lua_register_event_queue
 * Registers Event_queue functionality to the lua state.
 * */
int al_lua_register_event_queue (lua_State* L);

/* Function: al_lua_check_event_queue
 * Returns:
 * Pointer to Event_queue instance.
 * */
AL_Event_queue al_lua_check_event_queue (lua_State *L, int index);

/* Function: al_lua_set_event_callback
 * Each type of event source may have different data in the event
 * This function lets you register a function that fills in that data
 * */
void al_lua_set_event_callback(ALLEGRO_EVENT_TYPE event, void (*cb) (lua_State *L, ALLEGRO_EVENT *e)); 
