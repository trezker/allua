Test_mouse = {}

function Test_mouse:test00_prepare()
--	allegro5.init()
--	display = allegro5.display.create(800, 600)
end

function Test_mouse:test01_install()
	b = allegro5.mouse.install ()
	installed = allegro5.mouse.is_installed ()
	--mouse = allegro5.mouse.get()
	assertEquals("boolean", type(b))
	assertEquals("boolean", type(installed))
	--assertEquals("mouse", tostring(mouse):sub(1, 5))
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

function Test_mouse:test03_get_event_source()
	s = allegro5.mouse.get_event_source ()
	assertEquals("event_source", tostring(s):sub(1, 12))
end

function Test_mouse:test04_hide_cursor()
	b = allegro5.mouse.hide_cursor ()
	bs = allegro5.mouse.show_cursor ()
	assertEquals("boolean", type(b))
	assertEquals("boolean", type(bs))
end

function Test_mouse:test05_set_axis()
	b = allegro5.mouse.set_axis (0, 1)
	assertEquals("boolean", type(b))
end

function Test_mouse:test06_set_range()
	b = allegro5.mouse.set_range (0, 1, 2, 3)
	assertEquals("boolean", type(b))
end

function Test_mouse:test07_set_w()
	b = allegro5.mouse.set_w (10)
	assertEquals("boolean", type(b))
end

function Test_mouse:test08_set_xy()
	b = allegro5.mouse.set_xy (10, 20)
	assertEquals("boolean", type(b))
end

function Test_mouse:test09_uninstall()
	allegro5.mouse.uninstall ()
	display = nil
	collectgarbage()
end
