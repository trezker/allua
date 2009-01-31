allegro5.init()
display = Display.new(640, 480, Display.WINDOWED)
event_queue = Event_queue.new()

event_queue:register_event_source(display)
keyboard = Keyboard.get()
event_queue:register_event_source(keyboard)
mouse = Mouse.get()
event_queue:register_event_source(mouse)

bitmap = Bitmap.load("test/green_leaf.png")

font = Font.load_ttf("test/times.ttf", 24, 0)

mouse_x = 0
mouse_y = 0
mouse_z = 0

while not quit do
	event = event_queue:get_next_event()
	if event.type == Display.EVENT_CLOSE or event.type == Keyboard.EVENT_DOWN and event.keycode == Keyboard.KEY_ESCAPE then
		quit = true
	end

	if event.type == Mouse.EVENT_AXES then
		mouse_x = event.x
		mouse_y = event.y
		mouse_z = event.z
	end

	bitmap:draw(mouse_x, mouse_y, 0)

	font:textout(10, 10, "Mouse X:"..mouse_x, -1)

	Display.flip()
	Display.clear(Color.map_rgba(0, 0, 0, 0))
end
