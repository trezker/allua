require('luaunit')
require('liballua')
USE_EXPECTED_ACTUAL_IN_ASSERT_EQUALS = false
assertEqualsDelta = function(expected, actual, delta)
	assert(math.abs(expected-actual)<delta)
end
allegro5.init()
superdisplay = allegro5.display.create(800, 600)


Test_bitmap = {}

function Test_bitmap:test01_create()
	bitmap = allegro5.bitmap.create(100, 200)
	subbitmap = bitmap:create_sub(20, 30, 40, 50)
	bitmap_clone = bitmap:clone()
	assertEquals("bitmap", tostring(bitmap):sub(1, 6))
	assertEquals("bitmap", tostring(bitmap_clone):sub(1, 6))
	assertEquals("bitmap", tostring(subbitmap):sub(1, 6))

	assertEquals(true, subbitmap:is_sub())
	assertEquals(false, bitmap:is_sub())
end

function Test_bitmap:test02_new_flags()
	allegro5.bitmap.set_new_flags(0)
	getflags = allegro5.bitmap.get_new_flags()
	assertEquals("number", type(getflags))
end

function Test_bitmap:test03_new_format()
	allegro5.bitmap.set_new_format(0)
	getformat = allegro5.bitmap.get_new_format()
	assertEquals("number", type(getformat))
end

function Test_bitmap:test04_load()
	allegro5.bitmap.init_image_addon ()
	loadbitmap = allegro5.bitmap.load("data/leaf.png")
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

function Test_bitmap:test10_is_compatible()
	compatible = bitmap:is_compatible ()
	assertEquals("boolean", type(compatible))
end

function Test_bitmap:test11_clear_to_color()
	color = allegro5.color.map_rgba(1, 1, 1, 1)
	allegro5.bitmap.clear_to_color (color)
end

function Test_bitmap:test12_draw()
	bitmap:draw(1, 1, 0)
	bitmap:draw_region(1, 2, 3, 4, 5, 6, 0)
	bitmap:draw_rotated (1, 1, 2, 3, 2, 0)
	bitmap:draw_scaled_rotated  (1, 1, 2, 3, 2, .2, 1, 0)
	bitmap:draw_scaled (1, 1, 10, 10, 2, 2, 5, 20, 0)
end

function Test_bitmap:test13_get_target()
	allegro5.bitmap.set_target(bitmap)	
	gettarget1 = allegro5.bitmap.get_target ()
	allegro5.bitmap.set_target(superdisplay:get_backbuffer())
	assertEquals("bitmap", tostring(gettarget1):sub(1, 6))
	-- get_target and get_backbuffer create non_gc bitmap userdata so they can't be compared.
end

function Test_bitmap:test14_clipping_rectangle()
	sx, sy, sw, sh = 10, 20, 30, 40
	allegro5.bitmap.set_clipping_rectangle(sx, sy, sw, sh)
	x, y, w, h = allegro5.bitmap.get_clipping_rectangle()
	assertEquals("number", type(x))
	assertEquals("number", type(y))
	assertEquals("number", type(w))
	assertEquals("number", type(h))
	assertEquals(sx, x)
	assertEquals(sy, y)
	assertEquals(sw, w)
	assertEquals(sh, h)
end

function Test_bitmap:test15_convert_mask_to_alpha()
	color = allegro5.color.map_rgba(235, 26, 23, 100)
	bitmap:convert_mask_to_alpha (color)
end

function Test_bitmap:test20_cleanup()
	bitmap = nil
	subbitmap = nil
	bitmap_clone = nil
	loadbitmap = nil
	gettarget1 = nil
	collectgarbage()
end

LuaUnit:run() -- run all tests
