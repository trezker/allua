require('luaunit')
require('liballua')
USE_EXPECTED_ACTUAL_IN_ASSERT_EQUALS = false
assertEqualsDelta = function(expected, actual, delta)
	assert(math.abs(expected-actual)<delta)
end
allegro5.init()


Test_filesystem = {}

function Test_filesystem:test00_prepare()
end

function Test_filesystem:test01_functions()
	b = allegro5.filesystem.make_directory ("test_mkdir")
	exists = allegro5.filesystem.filename_exists ("test_mkdir")
	assertEquals("boolean", type(b))
	assertEquals(true, exists)
end

function Test_filesystem:test02_cleanup()
	collectgarbage()
end

LuaUnit:run() -- run all tests
