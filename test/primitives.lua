require('luaunit')
require('liballua')
USE_EXPECTED_ACTUAL_IN_ASSERT_EQUALS = false
assertEqualsDelta = function(expected, actual, delta)
	assert(math.abs(expected-actual)<delta)
end
allegro5.init()
superdisplay = allegro5.display.create(800, 600)


Test_primitives = {}

function Test_primitives:test00_prepare()
	allegro5.primitives.init_addon()
end

function Test_primitives:test01_functions()
	color = allegro5.color.map_rgba(123, 124, 156, 235)
	allegro5.primitives.draw_line (1, 2, 3, 4, color, 1)
	allegro5.primitives.draw_triangle (1, 2, 3, 4, 5, 6, color, 1)
	allegro5.primitives.draw_filled_triangle (1, 2, 3, 4, 5, 6, color)
	allegro5.primitives.draw_rectangle (1, 2, 3, 4, color, 1)
	allegro5.primitives.draw_filled_rectangle (1, 2, 3, 4, color)
	allegro5.primitives.draw_rounded_rectangle (1, 2, 11, 22, 3, 4, color, 1)
	allegro5.primitives.draw_filled_rounded_rectangle (1, 2, 11, 22, 3, 4, color)
	allegro5.primitives.draw_ellipse (1, 2, 3, 4, color, 1)
	allegro5.primitives.draw_filled_ellipse (1, 2, 3, 4, color)
	allegro5.primitives.draw_circle (1, 2, 3, color, 1)
	allegro5.primitives.draw_filled_circle (1, 2, 3, color)
	allegro5.primitives.draw_arc (1, 2, 3, 0, 1, color, 1)
end

function Test_primitives:test02_cleanup()
	display = nil
	color = nil
	collectgarbage()
end

LuaUnit:run() -- run all tests
