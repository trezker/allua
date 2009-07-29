Test_mixer = {}

function Test_mixer:test01_prepare()
	allegro5.init()
	allegro5.audio.install(allegro5.audio.AUDIO_DRIVER_AUTODETECT)
end

function Test_mixer:test02_create()
	mixer = allegro5.mixer.create (44100, allegro5.audio.AUDIO_DEPTH_FLOAT32, allegro5.audio.CHANNEL_CONF_2)
	assertEquals("mixer", tostring(mixer):sub(1, 5))
end

function Test_mixer:test20_destroy()
	mixer = nil
	collectgarbage()
end
