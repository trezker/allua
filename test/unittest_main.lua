require('luaunit')
require('liballua')

dofile("unittests/allegro5.lua")
dofile("unittests/display.lua")
dofile("unittests/bitmap.lua")
dofile("unittests/color.lua")

assertEqualsDelta = function(expected, actual, delta)
	assert(math.abs(expected-actual)<delta)
end

LuaUnit:run() -- run all tests
