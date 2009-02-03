allegro5.init()
display = allegro5.Display.new(640, 480, allegro5.Display.WINDOWED)
keyboard = allegro5.Keyboard.get()
event_queue = allegro5.Event_queue.new()
event_queue:register_event_source(display)
event_queue:register_event_source(keyboard)

pixels = 0
while not quit do
	event = event_queue:get_next_event()
	if event.type == allegro5.Display.EVENT_CLOSE or event.type == allegro5.Keyboard.EVENT_DOWN and event.keycode == allegro5.Keyboard.KEY_ESCAPE then
		quit = true
	end
	
	r = math.random(0, 255)
	g = math.random(0, 255)
	b = math.random(0, 255)
	color = allegro5.Color.map_rgba(r, g, b, 255)
	x1 = math.random(0, 640)
	y1 = math.random(0, 480)
	x2 = math.random(0, 640)
	y2 = math.random(0, 480)
	thickness = math.random(0, 4)
	allegro5.Primitives.draw_line_ex(x1, y1, x2, y2, color, thickness)

	pixels = pixels + 1
	
	allegro5.Display.flip()
end

print("Frames per second ", pixels / allegro5.current_time())
