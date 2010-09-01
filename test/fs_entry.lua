require('luaunit')
require('liballua')
USE_EXPECTED_ACTUAL_IN_ASSERT_EQUALS = false
assertEqualsDelta = function(expected, actual, delta)
	assert(math.abs(expected-actual)<delta)
end

allegro5.init()

Test_fs_entry = {}

function Test_fs_entry:test00_prepare()
end

function Test_fs_entry:test01_create()
	entry = allegro5.fs_entry.create ("../data/ball.png")
	assertEquals("fs_entry", tostring(entry):sub(1, 8))
end

function Test_fs_entry:test02_get_name()
	entry = allegro5.fs_entry.create ("../data/ball.png")
	path = entry:get_name()
	assertEquals("path", tostring(path):sub(1, 4))
end

function Test_fs_entry:test03_update()
	entry = allegro5.fs_entry.create ("../data/ball.png")
	b = entry:update()
	assertEquals("boolean", type(b))
end

function Test_fs_entry:test05_uninstall()
	s = nil
	collectgarbage()
end

LuaUnit:run() -- run all tests
