-- Title: mouse example
-- Demonstrates usage of mouse functions

allegro5.init()
display = allegro5.display.create(640, 480, allegro5.display.WINDOWED)
event_queue = allegro5.event_queue.new()

event_queue:register_event_source(display)
keyboard = allegro5.keyboard.get()
event_queue:register_event_source(keyboard)
mouse = allegro5.mouse.get()
event_queue:register_event_source(mouse)

bitmap = allegro5.bitmap.load("data/leaf.png")

font = allegro5.font.load_ttf("data/times.ttf", 16, 0)

mouse_x = 0
mouse_y = 0
mouse_z = 0
mouse_b = {}

while not quit do
	event = event_queue:get_next_event()
	if event.type == allegro5.display.EVENT_CLOSE or event.type == allegro5.keyboard.EVENT_DOWN and event.keycode == allegro5.keyboard.KEY_ESCAPE then
		quit = true
	end

	if event.type == allegro5.mouse.EVENT_AXES then
		mouse_x = event.x
		mouse_y = event.y
		mouse_z = event.z
	end

	if event.type == allegro5.mouse.EVENT_DOWN then
		mouse_b[event.button] = true
	end
	if event.type == allegro5.mouse.EVENT_UP then
		mouse_b[event.button] = false
	end

	bitmap:draw(mouse_x, mouse_y, 0)

	font:textout(10, 10, "mouse X:"..mouse_x, -1)
	font:textout(10, 30, "mouse Y:"..mouse_y, -1)
	font:textout(10, 50, "mouse Z:"..mouse_z, -1)
	
	y = 70
    for i,v in ipairs(mouse_b) do
     	font:textout(10, y, "mouse button " .. tostring(i) .. ": " .. tostring(v), -1)
     	y = y + 20
    end

	allegro5.display.flip()
	allegro5.display.clear(allegro5.color.map_rgba(0, 0, 0, 0))
end
