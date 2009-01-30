allegro5.init()
display = Display.new(640, 480, Display.WINDOWED)
event_queue = Event_queue.new()

event_queue:register_event_source(display)
pixels = 0
while not quit do
	event = event_queue:get_next_event()
	if event.type == Display.EVENT_CLOSE then
		quit = true
		print(event.type)
	end
	if event.type == Display.EVENT_SWITCH_OUT then
		print(event.type)
	end
	
	r = math.random(0, 255)
	g = math.random(0, 255)
	b = math.random(0, 255)
	color = Color.map_rgba(r, g, b, 0)
	x = math.random(0, 640)
	y = math.random(0, 480)
	Color.put_pixel(x, y, color)

	pixels = pixels + 1
	
	Display.flip()
end

print("Pixels per second ", pixels / allegro5.current_time())
