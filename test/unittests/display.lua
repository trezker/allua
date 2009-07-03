Test_display = {}

allegro5.init()

function Test_display:test01_create()
	display = allegro5.display.create(800, 600)
	assertEquals("display", tostring(display):sub(1, 7))
end

function Test_display:test02_get_num_display_formats()
	ndf = allegro5.display.get_num_display_formats()
	assert("number", type(ndf))
end

function Test_display:test03_get_format_option()
	value = allegro5.display.get_format_option(0, allegro5.display.COMPATIBLE_DISPLAY)
	assert("number", type(value))
end

function Test_display:test04_set_new_format()
	allegro5.display.set_new_format(0)
end

function Test_display:test05_new_flags()
	flags_set = allegro5.display.WINDOWED + allegro5.display.RESIZABLE
	allegro5.display.set_new_flags(flags_set)
	flags_get = allegro5.display.get_new_flags()
	assert("number", type(flags_get))
	assertEquals(flags_set, flags_get)
end

function Test_display:test06_new_refresh_rate()
	rate_set = 70
	allegro5.display.set_new_refresh_rate(rate_set)
	rate_get = allegro5.display.get_new_refresh_rate()
	assert("number", type(rate_get))
	assertEquals(rate_set, rate_get)
end

function Test_display:test07_new_window_position()
	set_x, set_y = 70, 40
	allegro5.display.set_new_window_position(set_x, set_y)
	get_x, get_y = allegro5.display.get_new_window_position()
	assert("number", type(get_x))
	assert("number", type(get_y))
	assertEquals(set_x, get_x)
	assertEquals(set_y, get_y)
end

function Test_display:test08_new_option()
	value_set = 2
	importance_set = allegro5.display.REQUIRE
	allegro5.display.set_new_option(allegro5.display.VSYNC, value_set, importance_set)
	value_get, importance_get = allegro5.display.get_new_option(allegro5.display.VSYNC)
	allegro5.display.reset_new_options()
	assert("number", type(value_get))
	assert("number", type(importance_get))
	assertEquals(value_set, value_get)
	assertEquals(importance_set, importance_get)
end

function Test_display:test09_flip()
	allegro5.display.flip()
end

function Test_display:test10_buffers()
	bb = display:get_backbuffer()
	fb = display:get_frontbuffer()
	assertEquals("bitmap", tostring(bb):sub(1, 6))
	assertEquals("bitmap", tostring(fb):sub(1, 6))
end

function Test_display:test11_current()
	d2 = allegro5.display.create(800, 600)
	ca = allegro5.display.get_current()
	display:set_current()
	cb = allegro5.display.get_current()
	assertEquals(d2, ca)
	assertEquals(display, cb)
end

function Test_display:test12_get()
	gflags = allegro5.display.get_flags()
	gformat = allegro5.display.get_format()
	gheight = allegro5.display.get_height()
	grefresh_rate = allegro5.display.get_refresh_rate()
	gwidth = allegro5.display.get_width()
	assertEquals("number", type(gflags))
	assertEquals("number", type(gformat))
	assertEquals("number", type(gheight))
	assertEquals("number", type(grefresh_rate))
	assertEquals("number", type(gwidth))
	gfrontbuffer = allegro5.display.get_frontbuffer()
	assertEquals("bitmap", tostring(gfrontbuffer):sub(1, 6))
end

function Test_display:test13_inhibit_screensaver()
	gb = allegro5.display.inhibit_screensaver()
	assertEquals("boolean", type(gb))
end

function Test_display:test14_resize()
	gb = allegro5.display.resize(640, 480)
	assertEquals("boolean", type(gb))
	assertEquals(true, gb)
end

function Test_display:test15_icon()
	i = allegro5.bitmap.create(16, 16)
	allegro5.display.set_icon(i)
end

function Test_display:test16_get_option()
	i = allegro5.display.VSYNC
	o = allegro5.display.get_option(i)
	assertEquals("number", type(o))
end

function Test_display:test17_window_position()
	display:set_window_position(100, 50)
	gpx, gpy = display:get_window_position()
	assertEquals("number", type(gpx))
	assertEquals("number", type(gpy))
	--Doesn't work in compiz (Allegro hasn't implemented get yet)
--	assertEquals(100, gpx)
--	assertEquals(50, gpy)
end

function Test_display:test18_window_title()
	allegro5.display.set_window_title("A title")
end

function Test_display:test19_toggle_window_frame()
	display:toggle_window_frame(true)
end

function Test_display:test20_update_region()
	allegro5.display.update_region(10, 10, 100, 100)
end
