allegro5.init()
display = Display.new(640, 480, Display.WINDOWED)
event_queue = Event_queue.new()

event_queue:register_event_source(display)
keyboard = allegro5.Keyboard.get()
event_queue:register_event_source(keyboard)
mouse = allegro5.Mouse.get()
event_queue:register_event_source(mouse)

bitmap = allegro5.Bitmap.load("test/green_leaf.png")

font = allegro5.Font.load_ttf("test/times.ttf", 16, 0)

mouse_x = 0
mouse_y = 0
mouse_z = 0
mouse_b = {}

while not quit do
	event = event_queue:get_next_event()
	if event.type == Display.EVENT_CLOSE or event.type == allegro5.Keyboard.EVENT_DOWN and event.keycode == allegro5.Keyboard.KEY_ESCAPE then
		quit = true
	end

	if event.type == allegro5.Mouse.EVENT_AXES then
		mouse_x = event.x
		mouse_y = event.y
		mouse_z = event.z
	end

	if event.type == allegro5.Mouse.EVENT_DOWN then
		mouse_b[event.button] = true
	end
	if event.type == allegro5.Mouse.EVENT_UP then
		mouse_b[event.button] = false
	end

	bitmap:draw(mouse_x, mouse_y, 0)

	font:textout(10, 10, "Mouse X:"..mouse_x, -1)
	font:textout(10, 30, "Mouse Y:"..mouse_y, -1)
	font:textout(10, 50, "Mouse Z:"..mouse_z, -1)
	
	y = 70
    for i,v in ipairs(mouse_b) do
     	font:textout(10, y, "Mouse button " .. tostring(i) .. ": " .. tostring(v), -1)
     	y = y + 20
    end

	Display.flip()
	Display.clear(Color.map_rgba(0, 0, 0, 0))
end
