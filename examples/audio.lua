-- Title: primitives example
-- Demonstrates usage of primitives functions
require('liballua')

allegro5.init()
allegro5.audio.install()
allegro5.audio.init_acodec_addon()
sample = allegro5.sample.load("data/powerup.ogg")
if not sample then
	print("Couldn't load")
else
	print("Sample loaded")
end

instance = sample:create_instance ()
voice = allegro5.voice.create (44100, allegro5.audio.AUDIO_DEPTH_FLOAT32, allegro5.audio.CHANNEL_CONF_2)
mixer = allegro5.mixer.create (44100, allegro5.audio.AUDIO_DEPTH_FLOAT32, allegro5.audio.CHANNEL_CONF_2)
mixer:attach_voice(voice)
attached = mixer:attach_sample(instance)


playing = instance:play()
if playing then
	print("Playing sample")
	while instance:get_playing () do
	end
else
	print("Could not play sample")
end
