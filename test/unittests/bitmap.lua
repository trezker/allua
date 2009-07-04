Test_bitmap = {}

allegro5.init()

function Test_bitmap:test01_create()
	bitmap = allegro5.bitmap.create(100, 200)
	subbitmap = bitmap:create_sub(20, 30, 40, 50)
	bitmap_clone = bitmap:clone()
	assertEquals("bitmap", tostring(bitmap):sub(1, 6))
	assertEquals("bitmap", tostring(bitmap_clone):sub(1, 6))
	assertEquals("bitmap", tostring(subbitmap):sub(1, 6))
end

function Test_bitmap:test02_new_flags()
	setflags = allegro5.bitmap.KEEP_BITMAP_FORMAT
	allegro5.bitmap.set_new_flags(setflags)
	getflags = allegro5.bitmap.get_new_flags()
	assertEquals("number", type(getflags))
	assertEquals(setflags, getflags)
end

function Test_bitmap:test03_new_format()
	setformat = 32
	allegro5.bitmap.set_new_format(setformat)
	getformat = allegro5.bitmap.get_new_format()
	allegro5.bitmap.set_new_format(0)
	assertEquals("number", type(getformat))
	assertEquals(setformat, getformat)
end

function Test_bitmap:test04_load()
	loadbitmap = allegro5.bitmap.load("data/test.png")
	assertEquals("bitmap", tostring(loadbitmap):sub(1, 6))
end

function Test_bitmap:test05_flags()
	getflags = bitmap:get_flags()
	assertEquals("number", type(getflags))
end

function Test_bitmap:test06_format()
	getformat = bitmap:get_format()
	assertEquals("number", type(getformat))
end

function Test_bitmap:test07_get_size()
	getw = bitmap:get_width ()
	geth = bitmap:get_height  ()
	assertEquals("number", type(getw))
	assertEquals("number", type(geth))
end

function Test_bitmap:test08_get_pixel()
	getpixel = bitmap:get_pixel (0, 0)
	assertEquals("color", tostring(getpixel):sub(1, 5))
end

function Test_bitmap:test09_lock()
	locked = bitmap:is_locked ()
	assertEquals("boolean", type(locked))
end
