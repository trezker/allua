-- Title: Pixels example
-- Demonstrates usage of Pixel functions
require('liballua')

allegro5.init()
allegro5.keyboard.install()
allegro5.mouse.install()
allegro5.bitmap.init_image_addon ()
allegro5.font.init_addon()

display = allegro5.display.create(640, 480, allegro5.display.WINDOWED)
event_queue = allegro5.event_queue.create()

event_queue:register_event_source(display:get_event_source())
pixels = 0
while not quit do
	event = event_queue:get_next_event()
	if event.type == allegro5.display.EVENT_CLOSE then
		quit = true
		print(event.type)
	end
	if event.type == allegro5.display.EVENT_SWITCH_OUT then
		print(event.type)
	end
	
	r = math.random(0, 255)
	g = math.random(0, 255)
	b = math.random(0, 255)
	color = allegro5.color.map_rgba(r, g, b, 0)
	x = math.random(0, 640)
	y = math.random(0, 480)
	color:put_pixel(x, y)

	pixels = pixels + 1
	
	allegro5.display.flip()
end

print("Pixels per second ", pixels / allegro5.current_time())
