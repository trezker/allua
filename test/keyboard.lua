allegro5.init()
display = Display.new(640, 480, Display.WINDOWED)
event_queue = Event_queue.new()

event_queue:register_event_source(display)
keyboard = Keyboard.get()
event_queue:register_event_source(keyboard)

pixels = 0
while not quit do
	event = event_queue:get_next_event()
	if event.type == Display.EVENT_CLOSE or event.type == Keyboard.EVENT_DOWN and event.keycode == Keyboard.KEY_ESCAPE then
		quit = true
	end
	
	if event.type then
		print("Event ", event.type)
	end
	
	if event.type == Keyboard.EVENT_DOWN then
		print("\tkey down", Keyboard.keycode_to_name(event.keycode))
		print("\tkeycode\t", event.keycode)
		print("\tunichar\t", event.unichar)
		print("\tmod\t", event.modifiers)
	end
	
	if event.type == Keyboard.EVENT_DOWN then
		if event.keycode == Keyboard.KEY_A then
			print("Thou hast presseth A")
		end
		if event.keycode == Keyboard.KEY_Z then
			print("Thou hast presseth Z")
		end
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
