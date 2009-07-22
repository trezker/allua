Test_sample_instance = {}

function Test_sample_instance:test01_prepare()
	allegro5.init()
	allegro5.audio.install(allegro5.audio.AUDIO_DRIVER_AUTODETECT)
	allegro5.audio.reserve_samples(2)
	sample = allegro5.sample.load("data/powerup.ogg")
	instance = sample:create_instance ()
	instance_no_data = allegro5.sample.create_instance (nil)
end

function Test_sample_instance:test02_play()
	bplay = instance:play()
	bstop = instance:stop()
	assertEquals("boolean", type(bplay))
	assertEquals("boolean", type(bstop))
end

function Test_sample_instance:test03_channels()
	channels = instance:get_channels ()
	assertEquals("number", type(channels))
end

function Test_sample_instance:test03_depth()
	depth = instance:get_depth ()
	assertEquals("number", type(depth))
end
