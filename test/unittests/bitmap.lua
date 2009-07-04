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
