require('luaunit')
require('liballua')
USE_EXPECTED_ACTUAL_IN_ASSERT_EQUALS = false
assertEqualsDelta = function(expected, actual, delta)
	assert(math.abs(expected-actual)<delta)
end
allegro5.init()
superdisplay = allegro5.display.create(800, 600)


Test_audio_stream = {}

function Test_audio_stream:test01_prepare()
--	allegro5.init()
	allegro5.audio.install(allegro5.audio.AUDIO_DRIVER_AUTODETECT)
	allegro5.audio.reserve_samples(2)
	ogg = allegro5.audio.init_ogg_vorbis_addon()
end

function Test_audio_stream:test02_create()
	audio_stream = allegro5.audio_stream.load ("data/powerup.ogg", 2, 2);
	assertEquals("audio_stream", tostring(audio_stream):sub(1, 12))
end

function Test_audio_stream:test03_rewind()
	b = audio_stream:rewind()
	assertEquals("boolean", type(b))
end

function Test_audio_stream:test03_frequency()
	f = audio_stream:get_frequency ()
	assertEquals("number", type(f))
end

function Test_audio_stream:test03_channels()
	c = audio_stream:get_channels ()
	assertEquals("number", type(c))
end

function Test_audio_stream:test03_depth()
	d = audio_stream:get_depth ()
	assertEquals("number", type(d))
end

function Test_audio_stream:test03_length()
	l = audio_stream:get_length ()
	assertEquals("number", type(l))
end

function Test_audio_stream:test03_speed()
	g = audio_stream:get_speed ()
	b = audio_stream:set_speed (1)
	assertEquals("number", type(g))
	assertEquals("boolean", type(b))
end

function Test_audio_stream:test03_gain()
	g = audio_stream:get_gain ()
	b = audio_stream:set_gain (1)
	assertEquals("number", type(g))
	assertEquals("boolean", type(b))
end

function Test_audio_stream:test03_pan()
	g = audio_stream:get_pan ()
	b = audio_stream:set_pan (1)
	assertEquals("number", type(g))
	assertEquals("boolean", type(b))
end

function Test_audio_stream:test03_playing()
	g = audio_stream:get_playing ()
	b = audio_stream:set_playing (true)
	assertEquals("boolean", type(g))
	assertEquals("boolean", type(b))
end

function Test_audio_stream:test03_playmode()
	g = audio_stream:get_playmode ()
	b = audio_stream:set_playmode (allegro5.audio.PLAYMODE_ONCE)
	assertEquals("number", type(g))
	assertEquals("boolean", type(b))
end

function Test_audio_stream:test04_attachment()
	g = audio_stream:get_attached ()
	b = audio_stream:detach ()
	assertEquals("boolean", type(g))
	assertEquals("boolean", type(b))
end

function Test_audio_stream:test05_seek()
	ss = audio_stream:seek_secs (0)
	p = audio_stream:get_position_secs()
	l = audio_stream:get_length_secs()
	lb = audio_stream:set_loop_secs(0, 1)
	assertEquals("boolean", type(ss))
	assertEquals("number", type(p))
	assertEquals("number", type(l))
	assertEquals("boolean", type(lb))
end

function Test_audio_stream:test10_cleanup()
	audio_stream = nil
	collectgarbage()
end

LuaUnit:run() -- run all tests
