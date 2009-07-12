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
