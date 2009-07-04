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
