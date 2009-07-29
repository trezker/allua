Test_mixer = {}

function Test_mixer:test01_prepare()
	allegro5.init()
	allegro5.audio.install(allegro5.audio.AUDIO_DRIVER_AUTODETECT)
	allegro5.audio.reserve_samples(2);
end

function Test_mixer:test02_create()
	mixer = allegro5.mixer.create (44100, allegro5.audio.AUDIO_DEPTH_FLOAT32, allegro5.audio.CHANNEL_CONF_2)
	assertEquals("mixer", tostring(mixer):sub(1, 5))
end

function Test_mixer:test03_default()
	default_mixer = allegro5.mixer.get_default ()
	b = default_mixer:set_default()
--	r = allegro5.mixer.restore_default() -- Causes sample play test to fail
	assertEquals("mixer", tostring(default_mixer):sub(1, 5))
	assertEquals("boolean", type(b))
--	assertEquals("boolean", type(r))
end

function Test_mixer:test04_attach()
	mixer2 = allegro5.mixer.create (44100, allegro5.audio.AUDIO_DEPTH_FLOAT32, allegro5.audio.CHANNEL_CONF_2)
	mb = mixer:attach_mixer(mixer2)

	sample = allegro5.sample.load("data/powerup.ogg")
	sample_instance = sample:create_instance()
	sampleb = mixer:attach_sample(sample_instance)

	stream = allegro5.stream.from_file(2, 2, "data/powerup.ogg")
	streamb = mixer:attach_stream (stream)
	
	assertEquals("boolean", type(mb))
	assertEquals("boolean", type(sampleb))
	assertEquals("boolean", type(streamb))
end

function Test_mixer:test20_destroy()
	mixer = nil
	collectgarbage()
end
