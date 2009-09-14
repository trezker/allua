-- Title: bitmap example
-- Demonstrates usage of bitmap functions

require('liballua')

allegro5.init()
allegro5.keyboard.install()
allegro5.mouse.install()
allegro5.bitmap.init_image_addon ()

allegro5.display.set_new_flags(allegro5.display.WINDOWED)
display = allegro5.display.create(640, 480)
event_queue = allegro5.event_queue.create()

event_queue:register_event_source(display:get_event_source())
keyboard = allegro5.keyboard.get_event_source()
event_queue:register_event_source(keyboard)
mouse = allegro5.mouse.get_event_source()
event_queue:register_event_source(mouse)

bitmap = allegro5.bitmap.load("data/leaf.png")
sub_bitmap = bitmap:create_sub(0, 0, 10, 10)
font = allegro5.font.load_ttf("data/times.ttf", 16, 0)

gctest_bitmap = allegro5.bitmap.load("data/leaf.png")
gctest_bitmap = nil

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

	bitmap:draw(10, 100, 0)
	sub_bitmap:draw(50, 100, 0)
	bitmap:draw_region(0, 10, 10, 10, 10, 150, 0)

	cx = bitmap:get_width()/2
	cy = bitmap:get_height()/2
	bitmap:draw_rotated(cx, cy, mouse_x, mouse_y, allegro5.current_time(), 0)

	allegro5.display.flip()
	allegro5.bitmap.clear_to_color (allegro5.color.map_rgba(0, 0, 0, 0))
	allegro5.rest(0.001)
end
