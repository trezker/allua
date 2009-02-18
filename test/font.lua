-- Title: Font example
-- Demonstrates usage of Font functions

allegro5.init()
display = allegro5.Display.new(640, 480, allegro5.Display.WINDOWED)
event_queue = allegro5.Event_queue.new()

event_queue:register_event_source(display)
keyboard = allegro5.Keyboard.get()
event_queue:register_event_source(keyboard)
mouse = allegro5.Mouse.get()
event_queue:register_event_source(mouse)

ttf_font = allegro5.Font.load_ttf("data/times.ttf", 24, 0)
image_font = allegro5.Font.load_image("data/font.tga")

while not quit do
	event = event_queue:get_next_event()
	if event.type == allegro5.Display.EVENT_CLOSE or event.type == allegro5.Keyboard.EVENT_DOWN and event.keycode == allegro5.Keyboard.KEY_ESCAPE then
		quit = true
	end
	
	ttf_font:textout(10, 10, "Wazzup! TTF font!", -1)
	image_font:textout(10, 50, "Wazzup! Image font!", -1)
	
	allegro5.Display.flip()
end
