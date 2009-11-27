require('luaunit')
require('liballua')
USE_EXPECTED_ACTUAL_IN_ASSERT_EQUALS = false
assertEqualsDelta = function(expected, actual, delta)
	assert(math.abs(expected-actual)<delta)
end
allegro5.init()
superdisplay = allegro5.display.create(800, 600)


Test_color = {}

function Test_color:test00_prepare()
--	allegro5.init()
end

function Test_color:test01_map()
	r, g, b, a = 1, 2, 3, 4
	rf, gf, bf, af = .1, .2, .3, .4
	rgb = allegro5.color.map_rgb(r, g, b)
	rgb_f = allegro5.color.map_rgb_f(rf, gf, bf)
	rgba = allegro5.color.map_rgba(r, g, b, a)
	rgba_f = allegro5.color.map_rgba_f(rf, gf, bf, af)

	assertEquals("color", tostring(rgba):sub(1, 5))
	assertEquals("color", tostring(rgb):sub(1, 5))
	assertEquals("color", tostring(rgb_f):sub(1, 5))

	g1r, g1g, g1b = rgb:unmap_rgb()
	g1rf, g1gf, g1bf = rgb_f:unmap_rgb_f()
	g2r, g2g, g2b, g2a = rgba:unmap_rgba()
	g2rf, g2gf, g2bf, g2af = rgba_f:unmap_rgba_f()
	
	--The commented values are because of a bug in allegro
	assertEquals(r, g1r)
	assertEquals(g, g1g)
	assertEquals(b, g1b)

	assertEquals(r, g2r)
	assertEquals(g, g2g)
	assertEquals(b, g2b)
	assertEquals(a, g2a)

	assertEqualsDelta(rf, g1rf, .001)
	assertEqualsDelta(gf, g1gf, .001)
	assertEqualsDelta(bf, g1bf, .001)

	assertEqualsDelta(rf, g2rf, .001)
	assertEqualsDelta(gf, g2gf, .001)
	assertEqualsDelta(bf, g2bf, .001)
	assertEqualsDelta(af, g2af, .001)
end

function Test_color:test02_put_pixel()
--	display = allegro5.display.create(800, 600)
	color = allegro5.color.map_rgb(2, 34, 4)
	color:put_pixel(24, 2)
	color:draw_pixel(24, 2)
end

function Test_color:test03_cleanup()
--	display = nil
	color = nil
	collectgarbage()
end

LuaUnit:run() -- run all tests
