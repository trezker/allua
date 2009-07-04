-- Title: font example
-- Demonstrates usage of font functions

allegro5.init()
display = allegro5.display.create(640, 480, allegro5.display.WINDOWED)
event_queue = allegro5.event_queue.new()

event_queue:register_event_source(display)
keyboard = allegro5.keyboard.get()
event_queue:register_event_source(keyboard)
mouse = allegro5.mouse.get()
event_queue:register_event_source(mouse)

ttf_font = allegro5.font.load_ttf("data/times.ttf", 24, 0)
image_font = allegro5.font.load_image("data/font.tga")

while not quit do
	event = event_queue:get_next_event()
	if event.type == allegro5.display.EVENT_CLOSE or event.type == allegro5.keyboard.EVENT_DOWN and event.keycode == allegro5.keyboard.KEY_ESCAPE then
		quit = true
	end
	
	ttf_font:textout(10, 10, "Wazzup! TTF font!", -1)
	image_font:textout(10, 50, "Wazzup! Image font!", -1)
	
	allegro5.display.flip()
end
