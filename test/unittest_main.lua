require('luaunit')

dofile("unittests/allegro5.lua")
dofile("unittests/display.lua")
dofile("unittests/bitmap.lua")

LuaUnit:run() -- run all tests
