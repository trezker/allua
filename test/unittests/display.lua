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
