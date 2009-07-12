Test_mouse = {}

allegro5.init()

function Test_mouse:test01_install()
	b = allegro5.mouse.install ()
	installed = allegro5.mouse.is_installed ()
	mouse = allegro5.mouse.get()
	assertEquals("boolean", type(b))
	assertEquals("boolean", type(installed))
	assertEquals(b, installed)
	assertEquals("keyboard", tostring(keyboard):sub(1, 8))
end
