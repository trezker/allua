require('luaunit')
require('liballua')
USE_EXPECTED_ACTUAL_IN_ASSERT_EQUALS = false
assertEqualsDelta = function(expected, actual, delta)
	assert(math.abs(expected-actual)<delta)
end
allegro5.init()
superdisplay = allegro5.display.create(800, 600)


Test_keyboard = {}

function Test_keyboard:test00_prepare()
--	allegro5.init()
end

function Test_keyboard:test01_install()
	b = allegro5.keyboard.install ()
	installed = allegro5.keyboard.is_installed ()
--	keyboard = allegro5.keyboard.get()
	assertEquals("boolean", type(b))
	assertEquals("boolean", type(installed))
	assertEquals(b, installed)
--	assertEquals("keyboard", tostring(keyboard):sub(1, 8))
end

function Test_keyboard:test02_keycode_to_name()
	key_name = allegro5.keyboard.keycode_to_name (allegro5.keyboard.KEY_UP)
	key_code = allegro5.keyboard.keycode_from_name (key_name)
	assertEquals("string", type(key_name))
	assertEquals(allegro5.keyboard.KEY_UP, key_code)
end

function Test_keyboard:test03_set_leds()
	b = allegro5.keyboard.set_leds (-1)
	assertEquals("boolean", type(b))
end

function Test_keyboard:test04_get_event_source()
	s = allegro5.keyboard.get_event_source ()
	assertEquals("event_source", tostring(s):sub(1, 12))
end

function Test_keyboard:test05_uninstall()
	s = nil
	collectgarbage()
	allegro5.keyboard.uninstall ()
end

LuaUnit:run() -- run all tests
