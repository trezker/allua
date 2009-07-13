-- Title: keyboard example
-- Demonstrates usage of keyboard functions
require('liballua')

allegro5.init()
allegro5.keyboard.install()
allegro5.mouse.install()
allegro5.bitmap.init_iio_addon ()
allegro5.font.init_addon()

display = allegro5.display.create(640, 480, allegro5.display.WINDOWED)
event_queue = allegro5.event_queue.create()

event_queue:register_event_source(display)
keyboard = allegro5.keyboard.get()
event_queue:register_event_source(keyboard)

print("Keycode of key \"Up\" is " .. tostring(allegro5.keyboard.keycode_from_name("Up")))

pixels = 0
while not quit do
	event = event_queue:get_next_event()
	if event.type == allegro5.display.EVENT_CLOSE or event.type == allegro5.keyboard.EVENT_DOWN and event.keycode == allegro5.keyboard.KEY_ESCAPE then
		quit = true
	end
	
	if event.type then
		print("Event ", event.type)
	end
	
	if event.type == allegro5.keyboard.EVENT_DOWN then
		print("\tkey down", allegro5.keyboard.keycode_to_name(event.keycode))
		print("\tkeycode\t", event.keycode)
		print("\tunichar\t", event.unichar)
		print("\tmod\t", event.modifiers)
	end
	
	if event.type == allegro5.keyboard.EVENT_DOWN then
		if event.keycode == allegro5.keyboard.KEY_A then
			print("Thou hast presseth A")
		end
		if event.keycode == allegro5.keyboard.KEY_Z then
			print("Thou hast presseth Z")
		end
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
