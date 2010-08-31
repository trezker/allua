require('luaunit')
require('liballua')
USE_EXPECTED_ACTUAL_IN_ASSERT_EQUALS = false
assertEqualsDelta = function(expected, actual, delta)
	assert(math.abs(expected-actual)<delta)
end

allegro5.init()

Test_path = {}

function Test_path:test00_prepare()
--	allegro5.init()
end

function Test_path:test01_create()
	path = allegro5.path.create ("../data/ball.png")
	path_dir = allegro5.path.create_for_directory ("../data/ball.png")
	assertEquals("path", tostring(path):sub(1, 4))
	assertEquals("path", tostring(path_dir):sub(1, 4))
end

function Test_path:test05_shutdown()
	s = nil
	collectgarbage()
end

LuaUnit:run() -- run all tests
