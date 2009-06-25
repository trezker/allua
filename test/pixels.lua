-- Title: Pixels example
-- Demonstrates usage of Pixel functions

allegro5.init()
display = allegro5.Display.create(640, 480, allegro5.Display.WINDOWED)
event_queue = allegro5.Event_queue.new()

event_queue:register_event_source(display)
pixels = 0
while not quit do
	event = event_queue:get_next_event()
	if event.type == allegro5.Display.EVENT_CLOSE then
		quit = true
		print(event.type)
	end
	if event.type == allegro5.Display.EVENT_SWITCH_OUT then
		print(event.type)
	end
	
	r = math.random(0, 255)
	g = math.random(0, 255)
	b = math.random(0, 255)
	color = allegro5.Color.map_rgba(r, g, b, 0)
	x = math.random(0, 640)
	y = math.random(0, 480)
	allegro5.Color.put_pixel(x, y, color)

	pixels = pixels + 1
	
	allegro5.Display.flip()
end

print("Pixels per second ", pixels / allegro5.current_time())
