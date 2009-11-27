require('luaunit')
require('liballua')
USE_EXPECTED_ACTUAL_IN_ASSERT_EQUALS = false
assertEqualsDelta = function(expected, actual, delta)
	assert(math.abs(expected-actual)<delta)
end
allegro5.init()
superdisplay = allegro5.display.create(800, 600)


Test_event_queue = {}

function Test_event_queue:test00_prepare()
--	allegro5.init()
end

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

function Test_event_queue:test04_flush()
	event_queue:flush ()
	b = event_queue:is_empty ()
	assertEquals("boolean", type(b))
	assertEquals(true, b)
end

function Test_event_queue:test05_get_peek_wait()
	get = event_queue:get_next_event ()
	peek = event_queue:peek_next_event ()
	wait_timed = event_queue:wait_for_event_timed (.1)
	assertEquals("table", type(get))
	assertEquals("table", type(peek))
	assertEquals("table", type(wait_timed))
end

function Test_event_queue:test06_register_source()
--	display = allegro5.display.create(800, 600)
	event_queue:register_event_source (superdisplay:get_event_source())
	event_queue:unregister_event_source (superdisplay:get_event_source())
end

function Test_event_queue:test07_destroy()
--	display = nil
	event_queue = nil
	collectgarbage()
end

LuaUnit:run() -- run all tests
