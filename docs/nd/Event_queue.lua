-- Class: event_queue

-- Function: create
-- Returns:
-- event_queue
function create () end

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
-- Parameters:
-- event_queue - event_queue
--
-- Returns:
-- A table with information about the event.
-- If there was an event, the field "type" holds the type of event.
-- If there was no event, the table is empty.
function get_next_event (event_queue) end

-- Function: peek_next_event
-- Parameters:
-- event_queue - event_queue
--
-- Returns:
-- A table with information about the event.
-- If there was an event, the field "type" holds the type of event.
-- If there was no event, the table is empty.
function peek_next_event (event_queue) end

-- Function: wait_for_event
-- Parameters:
-- event_queue - event_queue
--
-- Returns:
-- A table with information about the event.
-- the field "type" holds the type of event.
function wait_for_event (event_queue) end

-- Function: wait_for_event_timed
-- Parameters:
-- event_queue - event_queue
-- secs - number of seconds to wait
--
-- Returns:
-- A table with information about the event.
-- If there was an event, the field "type" holds the type of event.
-- If there was no event, the table is empty.
function wait_for_event_timed (event_queue, secs) end

-- Function: drop_next_event
-- Parameters:
-- event_queue - event_queue
--
-- Returns:
-- true if an event was dropped.
function drop_next_event (event_queue) end

-- Function: is_empty
-- Parameters:
-- event_queue - event_queue
--
-- Returns:
-- true if the queue is empty.
function is_empty (event_queue) end

-- Function: flush
-- Parameters:
-- event_queue - event_queue
function flush (event_queue) end
