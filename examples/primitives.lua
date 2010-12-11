-- Title: primitives example
-- Demonstrates usage of primitives functions
require('liballua')

allegro5.init()
allegro5.keyboard.install()
allegro5.mouse.install()
allegro5.bitmap.init_image_addon ()
allegro5.font.init_addon()
allegro5.primitives.init_addon()

display = allegro5.display.create(640, 480, allegro5.display.WINDOWED)
keyboard = allegro5.keyboard.get_event_source()
event_queue = allegro5.event_queue.create()
event_queue:register_event_source(display:get_event_source())
event_queue:register_event_source(keyboard)

red = allegro5.color.map_rgba(255, 0, 0, 255)
green = allegro5.color.map_rgba(0, 255, 0, 255)
blue = allegro5.color.map_rgba(0, 0, 255, 255)
black = allegro5.color.map_rgba(0, 0, 0, 255)

last_time = 0
a1 = 0
a2 = 0

pixels = 0
while not quit do
	event = event_queue:get_next_event()
	if event.type == allegro5.display.EVENT_CLOSE or event.type == allegro5.keyboard.EVENT_DOWN and event.keycode == allegro5.keyboard.KEY_ESCAPE then
		quit = true
	end
	
	current_time = allegro5.current_time()
	dt = current_time - last_time
	last_time = current_time

	x1 = 10
	y1 = 10 + math.sin(current_time) * 10
	x2 = 100
	y2 = 10 + math.cos(current_time) * 10

--	allegro5.primitives.draw_line(x1, y1, x2, y2, red)
	thickness = 0
	while thickness < 10 do
		allegro5.primitives.draw_line(x1, y1, x2, y2, red, thickness)
		thickness = thickness + 2
		y1 = y1 + 10
		y2 = y2 + 10
	end

--	y1 = y1 + 20
--	y2 = y2 + 20

	thickness = 5 + math.cos(current_time) * 5
	x3 = 50 + math.cos(current_time) * 10
	y3 = 100 + math.sin(current_time) * 10
	allegro5.primitives.draw_triangle(x1, y1, x2, y2, x3, y3, green, thickness)
	y1 = y1 + 50
	y2 = y2 + 50
	y3 = y3 + 50
	allegro5.primitives.draw_filled_triangle(x1, y1, x2, y2, x3, y3, green)

	y1 = y1 + 50
	y2 = y2 + 100
	allegro5.primitives.draw_rectangle(x1, y1, x2, y2, green, thickness)

	y1 = y1 + 50
	y2 = y2 + 50
	allegro5.primitives.draw_filled_rectangle(x1, y1, x2, y2, green)

	x1 = x1 + 50
	y1 = y1 + 100
	allegro5.primitives.draw_ellipse(x1, y1, 50, 25, green, thickness)

	y1 = y1 + 50
	allegro5.primitives.draw_filled_ellipse(x1, y1, 50, 25, green)

	x1 = 160
	y1 = 50
	allegro5.primitives.draw_circle(x1, y1, 50, blue, thickness)
	y1 = y1 + 110
	allegro5.primitives.draw_filled_circle(x1, y1, 50, blue)

	y1 = y1 + 110

	if a1 > math.pi * 2 then
		a1 = 0
	end
	if a1 ~= 0 then
		allegro5.primitives.draw_arc(x1, y1, 50, a1, a1, blue, thickness)
	end
	a1 = a1 + dt

	pixels = pixels + 1

	allegro5.display.flip()
	allegro5.bitmap.clear_to_color (black)
end

print("Frames per second ", pixels / allegro5.current_time())
