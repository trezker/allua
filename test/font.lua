-- Title: font example
-- Demonstrates usage of font functions
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
mouse = allegro5.mouse.get()
event_queue:register_event_source(mouse)

ttf_font = allegro5.font.load_ttf("data/times.ttf", 24, 0)
image_font = allegro5.font.load_bitmap("data/font.tga")

while not quit do
	event = event_queue:get_next_event()
	if event.type == allegro5.display.EVENT_CLOSE or event.type == allegro5.keyboard.EVENT_DOWN and event.keycode == allegro5.keyboard.KEY_ESCAPE then
		quit = true
	end
	
	ttf_font:draw_text(10, 10, 0, "Wazzup! TTF font!")
	image_font:draw_text(10, 50, 0, "Wazzup! Image font!")
	
	allegro5.display.flip()
end
