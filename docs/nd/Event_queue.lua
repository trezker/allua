-- Class: Event_queue

-- Function: new
-- Returns:
-- Event_queue
function new () end

-- Function: register_event_source
-- Parameters:
-- event_queue - Event_queue to which registering is done
-- event_source - Event_source
function register_event_source (event_queue, event_source) end

-- Function: unregister_event_source
-- Parameters:
-- event_queue - Event_queue to which unregistering is done
-- event_source - Event_source
function unregister_event_source (event_queue, event_source) end

-- Function: get_next_event
-- Returns:
-- A table with information about the event.
-- If there was an event, the field "type" holds the type of event.
-- If there was no event, the table is empty.
function get_next_event () end
