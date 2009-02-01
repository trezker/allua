allegro5.init()
display = Display.new(640, 480, Display.WINDOWED)
event_queue = Event_queue.new()

event_queue:register_event_source(display)
keyboard = Keyboard.get()
event_queue:register_event_source(keyboard)
mouse = Mouse.get()
event_queue:register_event_source(mouse)

bitmap = Bitmap.load("test/green_leaf.png")

ttf_font = allegro5.Font.load_ttf("test/times.ttf", 24, 0)
image_font = allegro5.Font.load_image("test/font.tga")

pixels = 0
while not quit do
	event = event_queue:get_next_event()
	if event.type == Display.EVENT_CLOSE or event.type == Keyboard.EVENT_DOWN and event.keycode == Keyboard.KEY_ESCAPE then
		quit = true
	end
	
	ttf_font:textout(10, 10, "Wazzup! TTF font!", -1)
	image_font:textout(10, 50, "Wazzup! Image font!", -1)
	
	Display.flip()
end
