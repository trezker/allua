Test_keyboard = {}

allegro5.init()

function Test_keyboard:test01_install()
	b = allegro5.keyboard.install ()
	installed = allegro5.keyboard.is_installed ()
	keyboard = allegro5.keyboard.get()
	assertEquals("boolean", type(b))
	assertEquals("boolean", type(installed))
	assertEquals(b, installed)
	assertEquals("keyboard", tostring(keyboard):sub(1, 8))
end

function Test_keyboard:test01_keycode_to_name()
	key_name = allegro5.keyboard.keycode_to_name (allegro5.keyboard.KEY_UP)
	key_code = allegro5.keyboard.keycode_from_name (key_name)
	assertEquals("string", type(key_name))
	assertEquals(allegro5.keyboard.KEY_UP, key_code)
end
