Test_bitmap = {}

allegro5.init()

function Test_bitmap:test01_create()
	bitmap = allegro5.bitmap.create(100, 200)
	assertEquals("bitmap", tostring(bitmap):sub(1, 6))
end

function Test_bitmap:test02_clone()
	bitmap = allegro5.bitmap.create(100, 200)
	bitmap_clone = bitmap:clone()
	assertEquals("bitmap", tostring(bitmap_clone):sub(1, 6))
end
