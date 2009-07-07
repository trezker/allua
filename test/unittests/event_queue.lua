Test_event_queue = {}

allegro5.init()

function Test_event_queue:test01_create()
	event_queue = allegro5.event_queue.create()
	assertEquals("event_queue", tostring(event_queue):sub(1, 11))
end
