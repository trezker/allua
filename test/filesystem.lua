require('luaunit')
require('liballua')
USE_EXPECTED_ACTUAL_IN_ASSERT_EQUALS = false
assertEqualsDelta = function(expected, actual, delta)
	assert(math.abs(expected-actual)<delta)
end
allegro5.init()
--superdisplay = allegro5.display.create(800, 600)


Test_filesystem = {}

function Test_filesystem:test00_prepare()
--	allegro5.init()
--	display = allegro5.display.create(800, 600)
end

function Test_filesystem:test01_functions()
	b = allegro5.filesystem.make_directory ("test_mkdir")
	assertEquals("boolean", type(b))
end

function Test_filesystem:test02_cleanup()
--	display = nil
	collectgarbage()
end

LuaUnit:run() -- run all tests
