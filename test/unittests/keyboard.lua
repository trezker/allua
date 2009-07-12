Test_keyboard = {}

allegro5.init()

function Test_keyboard:test01_install()
	b = allegro5.keyboard.install ()
	assertEquals("boolean", type(b))
end
