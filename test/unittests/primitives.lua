Test_primitives = {}

allegro5.init()

function Test_primitives:test01_functions()
	color = allegro5.color.map_rgba(123, 124, 156, 235)
	allegro5.primitives.draw_line (1, 2, 3, 4, color, 1)
	allegro5.primitives.draw_triangle (1, 2, 3, 4, 5, 6, color, 1)
	allegro5.primitives.draw_filled_triangle (1, 2, 3, 4, 5, 6, color)
	allegro5.primitives.draw_rectangle (1, 2, 3, 4, color, 1)
	allegro5.primitives.draw_filled_rectangle (1, 2, 3, 4, color)
end
