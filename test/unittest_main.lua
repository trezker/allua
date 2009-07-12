require('luaunit')
require('liballua')

dofile("unittests/allegro5.lua")
dofile("unittests/display.lua")
dofile("unittests/bitmap.lua")
dofile("unittests/color.lua")
dofile("unittests/event_queue.lua")
dofile("unittests/font.lua")
dofile("unittests/keyboard.lua")
dofile("unittests/mouse.lua")

assertEqualsDelta = function(expected, actual, delta)
	assert(math.abs(expected-actual)<delta)
end

LuaUnit:run() -- run all tests
