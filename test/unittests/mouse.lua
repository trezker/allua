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

function Test_mouse:test02_get_cursor_position()
	x, y = allegro5.mouse.get_cursor_position ()
	if x then
		assertEquals("number", type(x))
		assertEquals("number", type(y))
	end
end

function Test_mouse:test03_get_stuff()
	axes = allegro5.mouse.get_num_axes ()
	buttons = allegro5.mouse.get_num_buttons ()
	assertEquals("number", type(axes))
	assertEquals("number", type(buttons))
end

function Test_mouse:test04_hide_cursor()
	b = allegro5.mouse.hide_cursor ()
	assertEquals("boolean", type(b))
end
