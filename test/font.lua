require('luaunit')
require('liballua')
USE_EXPECTED_ACTUAL_IN_ASSERT_EQUALS = false
assertEqualsDelta = function(expected, actual, delta)
	assert(math.abs(expected-actual)<delta)
end


Test_font = {}

function Test_font:test00_prepare()
	allegro5.init()
	allegro5.bitmap.init_image_addon()
	superdisplay = allegro5.display.create(800, 600)
end

function Test_font:test01_init()
	allegro5.font.init_addon ()
	b = allegro5.font.init_ttf_addon ()
	assertEquals("boolean", type(b))
end

function Test_font:test03_load_ttf()
	ttf_font_fail = allegro5.font.load_ttf("a.ttf", 23, 0)
	ttf_font = allegro5.font.load_ttf("data/times.ttf", 23, 0)
	assertEquals("nil", type(ttf_font_fail))
	assertEquals("font", tostring(ttf_font):sub(1, 4))
end

function Test_font:test04_load_bitmap()
	bitmap_font_fail = allegro5.font.load_bitmap("a.tga")
	bitmap_font = allegro5.font.load_bitmap("data/font.tga")
	assertEquals("nil", type(bitmap_font_fail))
	assertEquals("font", tostring(bitmap_font):sub(1, 4))
end

function Test_font:test05_draw_text()
	color = allegro5.color.map_rgb(1, 1, 1)
	ttf_font:draw_text (color, 10, 10, 0, "times.ttf")
	bitmap_font:draw_text (color, 10, 40, 0, "font.tga")
	ttf_font:draw_justified_text (color, 10, 100, 10, 0, 0, "times.ttf")
end

function Test_font:test06_text_dimensions()
	bbx, bby, bbw, bbh = ttf_font:get_text_dimensions ("times.ttf")
	line_height = ttf_font:get_line_height ()
	width = ttf_font:get_text_width ("times.ttf")
	assertEquals("number", type(bbx))
	assertEquals("number", type(bby))
	assertEquals("number", type(bbw))
	assertEquals("number", type(bbh))
	assertEquals("number", type(line_height))
	assertEquals("number", type(width))
end

function Test_font:test07_cleanup()
--	display = nil
	ttf_font = nil
	bitmap_font = nil
	collectgarbage()
end

LuaUnit:run() -- run all tests
