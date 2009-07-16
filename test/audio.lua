-- Title: primitives example
-- Demonstrates usage of primitives functions
require('liballua')

allegro5.init()
allegro5.audio.install(allegro5.audio.AUDIO_DRIVER_AUTODETECT)
sample = allegro5.sample.load("powerup.ogg")
if not sample then
	print("Couldn't load")
else
	print("Sample loaded")
end
