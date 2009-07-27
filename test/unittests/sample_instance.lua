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

function Test_sample_instance:test03_frequency()
	frequency = instance:get_frequency ()
	assertEquals("number", type(frequency))
end

function Test_sample_instance:test03_length()
	length = instance:get_length ()
	b = instance:set_length (length)
	assertEquals("number", type(length))
	assertEquals("boolean", type(b))
end

function Test_sample_instance:test03_position()
	position = instance:get_position ()
	b = instance:set_position (0)
	assertEquals("number", type(position))
	assertEquals("boolean", type(b))
end

function Test_sample_instance:test03_speed()
	speed = instance:get_speed ()
	b = instance:set_speed (1)
	assertEquals("number", type(speed))
	assertEquals("boolean", type(b))
end

function Test_sample_instance:test03_gain()
	gain = instance:get_gain ()
	b = instance:set_gain (1)
	assertEquals("number", type(gain))
	assertEquals("boolean", type(b))
end

function Test_sample_instance:test03_pan()
	pan = instance:get_pan ()
	b = instance:set_pan (0)
	assertEquals("number", type(pan))
	assertEquals("boolean", type(b))
end

function Test_sample_instance:test03_time()
	gtime = instance:get_time ()
	assertEquals("number", type(gtime))
end

function Test_sample_instance:test03_playmode()
	playmode = instance:get_playmode ()
	b = instance:set_playmode (allegro5.audio.PLAYMODE_ONCE)
	assertEquals("number", type(playmode))
	assertEquals("boolean", type(b))
end

function Test_sample_instance:test03_playing()
	playing = instance:get_playing ()
	b = instance:set_playing (false)
	assertEquals("boolean", type(playing))
	assertEquals("boolean", type(b))
end

function Test_sample_instance:test03_attached()
	attached = instance:get_attached ()
	assertEquals("boolean", type(attached))
end

function Test_sample_instance:test03_get_sample()
	gsample = instance:get_sample ()
	assertEquals("sample", tostring(gsample):sub(1, 6))
end

function Test_sample_instance:test04_shutdown()
	gsample = nil
	print(tostring(instance))
	instance = nil
	print(tostring(instance_no_data))
	instance_no_data = nil
	collectgarbage()
	print(tostring(sample))
	sample = nil
	collectgarbage()
end
