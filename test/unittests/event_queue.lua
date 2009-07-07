Test_event_queue = {}

allegro5.init()

function Test_event_queue:test01_create()
	event_queue = allegro5.event_queue.create()
	assertEquals("event_queue", tostring(event_queue):sub(1, 11))
end

function Test_event_queue:test02_drop_next()
	b = event_queue:drop_next_event ()
	assertEquals("boolean", type(b))
end

function Test_event_queue:test03_is_empty()
	b = event_queue:is_empty ()
	assertEquals("boolean", type(b))
end
