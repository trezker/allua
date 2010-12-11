require('luaunit')
require('liballua')
USE_EXPECTED_ACTUAL_IN_ASSERT_EQUALS = false
assertEqualsDelta = function(expected, actual, delta)
	assert(math.abs(expected-actual)<delta)
end
allegro5.init()
superdisplay = allegro5.display.create(800, 600)


Test_display = {}

function Test_display:test00_prepare()
--	allegro5.init()
end

function Test_display:test01_create()
	display = allegro5.display.create(800, 600)
	assertEquals("display", tostring(display):sub(1, 7))
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
	assertEquals("bitmap", tostring(bb):sub(1, 6))
end

function Test_display:test11_current()
	d2 = allegro5.display.create(800, 600)
	ca = allegro5.display.get_current()
	display:set_current()
	cb = allegro5.display.get_current()
--	assertEquals(d2, ca)
	assertEquals(display, cb)
end

function Test_display:test12_get()
	gflags = display:get_flags()
	gformat = display:get_format()
	gheight = display:get_height()
	grefresh_rate = display:get_refresh_rate()
	gwidth = display:get_width()
	assertEquals("number", type(gflags))
	assertEquals("number", type(gformat))
	assertEquals("number", type(gheight))
	assertEquals("number", type(grefresh_rate))
	assertEquals("number", type(gwidth))
end

function Test_display:test13_inhibit_screensaver()
	gb = allegro5.display.inhibit_screensaver()
	assertEquals("boolean", type(gb))
end

function Test_display:test14_resize()
	gb = display:resize(640, 480)
	assertEquals("boolean", type(gb))
	assertEquals(true, gb)
end

function Test_display:test15_icon()
	i = allegro5.bitmap.create(16, 16)
	display:set_icon(i)
end

function Test_display:test16_get_option()
	i = allegro5.display.VSYNC
	o = display:get_option(i)
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
	display:set_window_title("A title")
end

function Test_display:test19_toggle_flag()
	fb = display:toggle_flag(NOFRAME, true)
	fwb = display:toggle_flag(FULLSCREEN_WINDOW, true)
	display:toggle_flag(NOFRAME, true)
	assertEquals("boolean", type(fb))
	assertEquals("boolean", type(fwb))
end

function Test_display:test20_update_region()
	allegro5.display.update_region(10, 10, 100, 100)
end

function Test_display:test21_vsync()
	gb = allegro5.display.wait_for_vsync()
	assertEquals("boolean", type(gb))
end

function Test_display:test22_modes()
	gnum = allegro5.display.get_num_modes()
	assertEquals("number", type(gnum))

	mode = allegro5.display.get_mode(0)
	if mode then
		assertEquals("number", type(mode.width))
		assertEquals("number", type(mode.height))
		assertEquals("number", type(mode.format))
		assertEquals("number", type(mode.refresh_rate))
	end
end

function Test_display:test23_cleanup()
	display = nil
	ca = nil
	cb = nil
	collectgarbage()
	superdisplay:set_current()
end

LuaUnit:run() -- run all tests
