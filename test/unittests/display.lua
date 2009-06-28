Test_display = {}

allegro5.init()

function Test_display:test1_create()
	display = allegro5.display.create(800, 600)
	assertEquals("display", tostring(display):sub(1, 7))
end

function Test_display:test2_get_num_display_formats()
	ndf = allegro5.display.get_num_display_formats()
	assert("number", type(ndf))
end

function Test_display:test3_get_format_option()
	value = allegro5.display.get_format_option(0, allegro5.display.COMPATIBLE_DISPLAY)
	assert("number", type(value))
end

function Test_display:test4_set_new_format()
	allegro5.display.set_new_format(0)
end

function Test_display:test5_new_flags()
	flags_set = allegro5.display.WINDOWED + allegro5.display.RESIZABLE
	allegro5.display.set_new_flags(flags_set)
	flags_get = allegro5.display.get_new_flags()
	assert("number", type(flags_get))
	assertEquals(flags_set, flags_get)
end

function Test_display:test6_new_refresh_rate()
	rate_set = 70
	allegro5.display.set_new_refresh_rate(rate_set)
	rate_get = allegro5.display.get_new_refresh_rate()
	assert("number", type(rate_get))
	assertEquals(rate_set, rate_get)
end

function Test_display:test7_new_window_position()
	set_x, set_y = 70, 40
	allegro5.display.set_new_window_position(set_x, set_y)
	get_x, get_y = allegro5.display.get_new_window_position()
	assert("number", type(get_x))
	assert("number", type(get_y))
	assertEquals(set_x, get_x)
	assertEquals(set_y, get_y)
end

function Test_display:test8_new_option()
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

