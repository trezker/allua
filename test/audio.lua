require('luaunit')
require('liballua')
USE_EXPECTED_ACTUAL_IN_ASSERT_EQUALS = false
assertEqualsDelta = function(expected, actual, delta)
	assert(math.abs(expected-actual)<delta)
end
allegro5.init()
superdisplay = allegro5.display.create(800, 600)


Test_audio = {}

function Test_audio:test00_prepare()
--	allegro5.init()
end

function Test_audio:test01_functions()
	install = allegro5.audio.install (allegro5.audio.AUDIO_DRIVER_AUTODETECT)
	reserve = allegro5.audio.reserve_samples (2)
	acodec = allegro5.audio.init_acodec_addon()
	allegro5.audio.uninstall ()
	assertEquals("boolean", type(install))
	assertEquals("boolean", type(reserve))
	assertEquals("boolean", type(acodec))
end

LuaUnit:run() -- run all tests
