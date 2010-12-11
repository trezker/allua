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
	path_clone = allegro5.path.clone (path)
	assertEquals("path", tostring(path):sub(1, 4))
	assertEquals("path", tostring(path_dir):sub(1, 4))
	assertEquals("path", tostring(path_clone):sub(1, 4))
end

function Test_path:test02_join()
	path1 = allegro5.path.create ("../data/")
	path2 = allegro5.path.create_for_directory ("ball.png")
	b = path1:join(path2)
	assertEquals("boolean", type(b))
end

function Test_path:test03_get_drive()
	path = allegro5.path.create ("../data/")
	drive = path:get_drive()
	assertEquals("string", type(drive))
end

function Test_path:test04_get_num_components()
	path = allegro5.path.create ("../data/")
	components = path:get_num_components()
	assertEquals("number", type(components))
end

function Test_path:test04_get_component()
	path = allegro5.path.create ("../data/")
	component = path:get_component(1)
	assertEquals("string", type(component))
end

function Test_path:test05_get()
	path = allegro5.path.create ("../data/ball.png")
	tail = path:get_tail()
	filename = path:get_filename()
	basename = path:get_basename()
	extension = path:get_extension()
	assertEquals("data", tail)
	assertEquals("ball.png", filename)
	assertEquals("ball", basename)
	assertEquals(".png", extension)
end

function Test_path:test06_set_drive()
	path = allegro5.path.create ("../data/")
	path:set_drive("C")
end

function Test_path:test07_append_component()
	path = allegro5.path.create ("../data/")
	path:append_component("ball.png")
end

function Test_path:test08_insert_component()
	path = allegro5.path.create ("../data/ball.png")
	path:insert_component(1, "balls")
end

function Test_path:test09_replace_component()
	path = allegro5.path.create ("../data/ball.png")
	path:replace_component(1, "balls")
end

function Test_path:test09_remove_component()
	path = allegro5.path.create ("../data/ball.png")
	path:remove_component(1)
end

function Test_path:test10_drop_tail()
	path = allegro5.path.create ("../data/ball.png")
	path:drop_tail()
end

function Test_path:test11_set()
	path = allegro5.path.create ("../data/ball.png")
	path:set_filename("tile.png")
	b = path:set_extension(".jpg")
	assertEquals("boolean", type(b))
end

function Test_path:test12_get_string()
	path = allegro5.path.create ("../data/ball.png")
	path_text = path:get_string()
	assertEquals("string", type(path_text))
end

function Test_path:test12_make_absolute_canonical()
	path = allegro5.path.create ("../data/ball.png")
	canonical = path:make_canonical()
	assertEquals("boolean", type(canonical))
end

function Test_path:test15_shutdown()
	path = nil
	collectgarbage()
end

LuaUnit:run() -- run all tests
