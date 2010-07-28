require('luaunit')
require('liballua')
USE_EXPECTED_ACTUAL_IN_ASSERT_EQUALS = false
assertEqualsDelta = function(expected, actual, delta)
	assert(math.abs(expected-actual)<delta)
end
allegro5.init()
superdisplay = allegro5.display.create(800, 600)


Test_native_dialog = {}

function Test_native_dialog:test01_create()
	native_dialog = allegro5.native_dialog.create ("", "test", "*.*", allegro5.native_dialog.FILECHOOSER_SAVE)
	assertEquals("native_dialog", tostring(native_dialog):sub(1, 13))
end

function Test_native_dialog:test02_show()
	native_dialog:show(superdisplay)
end

function Test_native_dialog:test03_get()
	n = native_dialog:get_count()
	if n>0 then
		path = native_dialog:get_path(0)
	else
		print("To test get_path you must select a file");
	end
	assertEquals("number", type(n))
	if n>0 then
		assertEquals("string", type(path))
	end
end

function Test_native_dialog:test10_destroy()
	native_dialog = nil
	collectgarbage()
end

LuaUnit:run() -- run all tests
