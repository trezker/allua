-- Title: primitives example
-- Demonstrates usage of primitives functions
require('liballua')

allegro5.init()
allegro5.audio.install(allegro5.audio.AUDIO_DRIVER_AUTODETECT)
allegro5.audio.init_ogg_vorbis_addon()
sample = allegro5.sample.load("data/powerup.ogg")
if not sample then
	print("Couldn't load")
else
	print("Sample loaded")
end
