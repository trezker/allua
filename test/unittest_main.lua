require('luaunit')
require('liballua')
USE_EXPECTED_ACTUAL_IN_ASSERT_EQUALS = false


dofile("unittests/allegro5.lua")
dofile("unittests/display.lua")
dofile("unittests/bitmap.lua")
dofile("unittests/color.lua")
dofile("unittests/event_queue.lua")
dofile("unittests/font.lua")
dofile("unittests/keyboard.lua")
dofile("unittests/mouse.lua")
dofile("unittests/primitives.lua")
dofile("unittests/audio.lua")
dofile("unittests/voice.lua")
dofile("unittests/sample.lua")
dofile("unittests/sample_instance.lua")
dofile("unittests/audio_stream.lua")
dofile("unittests/mixer.lua")

assertEqualsDelta = function(expected, actual, delta)
	assert(math.abs(expected-actual)<delta)
end

allegro5.init()
display = allegro5.display.create(800, 600)

LuaUnit:run() -- run all tests
