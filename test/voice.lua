require('luaunit')
require('liballua')
USE_EXPECTED_ACTUAL_IN_ASSERT_EQUALS = false
assertEqualsDelta = function(expected, actual, delta)
	assert(math.abs(expected-actual)<delta)
end
allegro5.init()
superdisplay = allegro5.display.create(800, 600)


Test_voice = {}

function Test_voice:test00_prepare()
--	allegro5.init()
	allegro5.audio.install(allegro5.audio.AUDIO_DRIVER_AUTODETECT)
end

function Test_voice:test01_create()
	voice = allegro5.voice.create (44100, allegro5.audio.AUDIO_DEPTH_INT8, allegro5.audio.CHANNEL_CONF_2)
	assertEquals("voice", tostring(voice):sub(1, 5))
end

function Test_voice:test02_destroy()
	voice = nil
	collectgarbage()
end

LuaUnit:run() -- run all tests
