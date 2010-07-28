require('luaunit')
require('liballua')
USE_EXPECTED_ACTUAL_IN_ASSERT_EQUALS = false
assertEqualsDelta = function(expected, actual, delta)
	assert(math.abs(expected-actual)<delta)
end
allegro5.init()
superdisplay = allegro5.display.create(800, 600)


Test_sample = {}

function Test_sample:test01_prepare()
--	allegro5.init()
	allegro5.audio.install(allegro5.audio.AUDIO_DRIVER_AUTODETECT)
	allegro5.audio.reserve_samples(2)
	allegro5.audio.init_acodec_addon()
end

function Test_sample:test02_load()
	sample = allegro5.sample.load("data/powerup.ogg")
	b = sample:save("data/powerup.wav")
	assertEquals("sample", tostring(sample):sub(1, 6))
	assertEquals("boolean", type(b))
end

function Test_sample:test03_play()
	b, sample_id = sample:play(1.0, 0.5, 1.0, allegro5.audio.PLAYMODE_ONCE)
	sample_id:stop()
	allegro5.sample.stop_samples ()
	assertEquals("boolean", type(b))
	assertEquals("sample_id", tostring(sample_id):sub(1, 9))
end

function Test_sample:test04_properties()
	channels = sample:get_channels()
	depth = sample:get_depth()
	frequency = sample:get_frequency()
	length = sample:get_length()
	assertEquals("number", type(channels))
	assertEquals("number", type(depth))
	assertEquals("number", type(frequency))
	assertEquals("number", type(length))
end

function Test_sample:test05_create_instance()
	instance = sample:create_instance ()
	instance_no_data = allegro5.sample.create_instance (nil)
	assertEquals("sample_instance", tostring(instance):sub(1, 15))
	assertEquals("sample_instance", tostring(instance_no_data):sub(1, 15))
end

function Test_sample:test06_shutdown()
	instance = nil
	instance_no_data = nil
--	collectgarbage()
	sample = nil
	collectgarbage()
	collectgarbage()
end

LuaUnit:run() -- run all tests
