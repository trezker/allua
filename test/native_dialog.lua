require('luaunit')
require('liballua')
USE_EXPECTED_ACTUAL_IN_ASSERT_EQUALS = false
assertEqualsDelta = function(expected, actual, delta)
	assert(math.abs(expected-actual)<delta)
end
allegro5.init()

Test_filechooser = {}

function Test_filechooser:test01_create()
	filechooser = allegro5.filechooser.create ("", "test", "*.*", allegro5.filechooser.FILECHOOSER_SAVE)
	assertEquals("filechooser", tostring(filechooser):sub(1, 11))
end

function Test_filechooser:test02_show()
	filechooser:show()
end

function Test_filechooser:test03_get()
	n = filechooser:get_count()
	if n>0 then
		path = filechooser:get_path(0)
	else
		print("To test get_path you must select a file");
	end
	assertEquals("number", type(n))
	if n>0 then
		assertEquals("string", type(path))
	end
end

function Test_filechooser:test10_destroy()
	filechooser = nil
	collectgarbage()
end

LuaUnit:run() -- run all tests
