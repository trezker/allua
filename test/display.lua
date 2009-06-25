-- Title: Display example
-- Demonstrates usage of Display functions

allegro5.init()
display0 = allegro5.Display.create(640, 480, allegro5.Display.WINDOWED)
display0 = nil
collectgarbage("collect")

display1 = allegro5.Display.create(640, 480, allegro5.Display.WINDOWED + allegro5.Display.RESIZABLE)
display2 = allegro5.Display.create(640, 480, allegro5.Display.WINDOWED)

event_queue = allegro5.Event_queue.new()

event_queue:register_event_source(display1)
event_queue:register_event_source(display2)
keyboard = allegro5.Keyboard.get()
event_queue:register_event_source(keyboard)
mouse = allegro5.Mouse.get()
event_queue:register_event_source(mouse)

bitmap = allegro5.Bitmap.load("data/leaf.png")

mouse_x = 0
mouse_y = 0
mouse_z = 0
mouse_b = {}

while not quit do
	event = event_queue:get_next_event()
	if event.type == allegro5.Keyboard.EVENT_DOWN and event.keycode == allegro5.Keyboard.KEY_ESCAPE then
		quit = true
	end

	if event.type == allegro5.Display.EVENT_CLOSE then
		if event.source == display2 then
			event_queue:unregister_event_source(display2)
			display2 = nil
			event.source = nil
		end
	end

	collectgarbage("collect")
	if event.type == allegro5.Display.EVENT_RESIZE then
		event.source:acknowledge_resize()
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


	if display2 then
		display2:set_current()
		cx = bitmap:width()/2
		cy = bitmap:height()/2
		bitmap:draw_rotated(cx, cy, mouse_x, mouse_y, allegro5.current_time(), 0)

		allegro5.Display.flip()
		allegro5.Display.clear(allegro5.Color.map_rgba(0, 0, 0, 0))
		allegro5.rest(0.001)
	end

	display1:set_current()
	bitmap:draw(10, 100, 0)

	allegro5.Display.flip()
	allegro5.Display.clear(allegro5.Color.map_rgba(0, 0, 0, 0))
	allegro5.rest(0.001)
end
