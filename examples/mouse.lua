-- Title: mouse example
-- Demonstrates usage of mouse functions
require('liballua')

allegro5.init()
allegro5.keyboard.install()
allegro5.mouse.install()
allegro5.bitmap.init_image_addon ()
allegro5.font.init_addon()
allegro5.font.init_ttf_addon()

display = allegro5.display.create(640, 480, allegro5.display.WINDOWED)
event_queue = allegro5.event_queue.create()

event_queue:register_event_source(display:get_event_source())
keyboard = allegro5.keyboard.get_event_source()
event_queue:register_event_source(keyboard)
mouse = allegro5.mouse.get_event_source()
event_queue:register_event_source(mouse)

bitmap = allegro5.bitmap.load("data/leaf.png")

font = allegro5.font.load_ttf("data/times.ttf", 16, 0)
text_color = allegro5.color.map_rgb_f(1, 1, 1, 1)

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

	font:draw_text(text_color, 10, 10, 0, "mouse X:"..mouse_x)
	font:draw_text(text_color, 10, 30, 0, "mouse Y:"..mouse_y)
	font:draw_text(text_color, 10, 50, 0, "mouse Z:"..mouse_z)
	
	y = 70
    for i,v in ipairs(mouse_b) do
     	font:draw_text(text_color, 10, y, 0, "mouse button " .. tostring(i) .. ": " .. tostring(v))
     	y = y + 20
    end

	allegro5.display.flip()
	allegro5.bitmap.clear_to_color(allegro5.color.map_rgba(0, 0, 0, 0))
end
