require('luaunit')
require('liballua')
USE_EXPECTED_ACTUAL_IN_ASSERT_EQUALS = false
assertEqualsDelta = function(expected, actual, delta)
	assert(math.abs(expected-actual)<delta)
end

Test_mixer = {}

function Test_mixer:test01_prepare()
	allegro5.init()
	allegro5.audio.install();
	allegro5.audio.init_acodec_addon();
end

function Test_mixer:test02_create()
	mixer = allegro5.mixer.create (44100, allegro5.audio.AUDIO_DEPTH_FLOAT32, allegro5.audio.CHANNEL_CONF_2)
	assertEquals("mixer", tostring(mixer):sub(1, 5))
end

--[[
function Test_mixer:test03_default()
	default_mixer = allegro5.mixer.get_default ()
	b = default_mixer:set_default()
--	r = allegro5.mixer.restore_default() -- Causes sample play test to fail
	assertEquals("mixer", tostring(default_mixer):sub(1, 5))
	assertEquals("boolean", type(b))
--	assertEquals("boolean", type(r))
end
--]]
function Test_mixer:test04_attach()
	voice = allegro5.voice.create (44100, allegro5.audio.AUDIO_DEPTH_FLOAT32, allegro5.audio.CHANNEL_CONF_2)
	mixer:attach_voice(voice)

	mixer2 = allegro5.mixer.create (44100, allegro5.audio.AUDIO_DEPTH_FLOAT32, allegro5.audio.CHANNEL_CONF_2)
	mb = mixer:attach_mixer(mixer2)

	sample = allegro5.sample.load("data/powerup.ogg")
	sample_instance = sample:create_instance()
	sampleb = mixer:attach_sample(sample_instance)

	stream = allegro5.audio_stream.load("data/powerup.ogg", 4, 2048)
	stream:set_playmode (allegro5.audio.PLAYMODE_ONCE)
	streamb = mixer:attach_audio_stream (stream)

	ab = mixer2:get_attached()
	db = mixer2:detach()

	assertEquals("boolean", type(mb))
	assertEquals("boolean", type(sampleb))
	assertEquals("boolean", type(streamb))
	assertEquals("boolean", type(ab))
	assertEquals("boolean", type(db))
end

function Test_mixer:test05_frequency()
	gfreq = mixer:get_frequency ()
	b = mixer:set_frequency(44100)
	assertEquals("number", type(gfreq))
	assertEquals("boolean", type(b))
end

function Test_mixer:test05_channels()
	gchannels = mixer:get_channels()
	assertEquals("number", type(gchannels))
end

function Test_mixer:test05_depth()
	gdepth = mixer:get_depth()
	assertEquals("number", type(gdepth))
end

function Test_mixer:test05_quality()
	gquality = mixer:get_quality()
	b = mixer:set_quality(allegro5.audio.MIXER_QUALITY_LINEAR)
	assertEquals("number", type(gquality))
	assertEquals("boolean", type(b))
end

function Test_mixer:test05_playing()
	gplaying = mixer:get_playing()
	b = mixer:set_playing(true)
	assertEquals("boolean", type(gplaying))
	assertEquals("boolean", type(b))
end

function Test_mixer:test20_destroy()
	sample_instance = nil
	sample = nil
	stream = nil
	mixer = nil
	mixer2 = nil
	collectgarbage()
	collectgarbage()
end

LuaUnit:run() -- run all tests
