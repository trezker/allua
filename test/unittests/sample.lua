Test_sample = {}



function Test_sample:test01_prepare()
	allegro5.init()
	allegro5.audio.install(allegro5.audio.AUDIO_DRIVER_AUTODETECT)
	allegro5.audio.reserve_samples(2)
end

function Test_sample:test02_load()
	sample = allegro5.sample.load("data/powerup.ogg")
	b = sample:save("data/powerup.wav")
	assertEquals("sample", tostring(sample):sub(1, 6))
	assertEquals("boolean", type(b))
end

function Test_sample:test03_play()
	b, sample_id = sample:play(1.0, 0.5, 1.0, allegro5.audio.PLAYMODE_ONCE)
	allegro5.sample.stop_samples ()
	assertEquals("boolean", type(b))
	assertEquals("sample_id", tostring(sample_id):sub(1, 9))
end

function Test_sample:test04_create_instance()
	instance = sample:create_instance ()
	instance_no_data = allegro5.sample.create_instance (nil)
	assertEquals("sample_instance", tostring(instance):sub(1, 15))
	assertEquals("sample_instance", tostring(instance_no_data):sub(1, 15))
end

