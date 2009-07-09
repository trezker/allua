Test_font = {}

allegro5.init()

function Test_font:test01_init()
	allegro5.font.init_addon ()
	b = allegro5.font.init_ttf_addon ()
	assertEquals("boolean", type(b))
end

function Test_font:test02_load_bitmap()
	font_fail = allegro5.font.load_bitmap("a.tga")
	ttf_font = allegro5.font.load_ttf("data/times.ttf", 23, 0)
	bitmap_font = allegro5.font.load_bitmap("data/font.tga")
	assertEquals("nil", type(bitmap_font_fail))
	assertEquals("font", tostring(bitmap_font):sub(1, 4))
	assertEquals("font", tostring(ttf_font):sub(1, 4))
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
	ttf_font:draw_text (10, 10, 0, "times.ttf")
	bitmap_font:draw_text (10, 40, 0, "font.tga")
	ttf_font:draw_justified_text (10, 100, 10, 0, 0, "times.ttf")
end

function Test_font:test06_text_dimensions()
	bbx, bby, bbw, bbh, ascent, descent = ttf_font:get_text_dimensions ("times.ttf")
	line_height = ttf_font:get_line_height ()
	width = ttf_font:get_text_width ("times.ttf")
	assertEquals("number", type(bbx))
	assertEquals("number", type(bby))
	assertEquals("number", type(bbw))
	assertEquals("number", type(bbh))
	assertEquals("number", type(ascent))
	assertEquals("number", type(descent))
	assertEquals("number", type(line_height))
	assertEquals("number", type(width))
end
