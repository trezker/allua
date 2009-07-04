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
	flags = allegro5.bitmap.get_new_flags()
	assertEquals("number", type(flags))
end

function Test_bitmap:test03_new_format()
	format = allegro5.bitmap.get_new_format()
	assertEquals("number", type(format))
end

function Test_bitmap:test04_load()
	loadbitmap = allegro5.bitmap.load("data/test.png")
	assertEquals("bitmap", tostring(loadbitmap):sub(1, 6))
end
