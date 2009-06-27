require('luaunit')

dofile("unittests/allegro5.lua")
dofile("unittests/display.lua")

LuaUnit:run() -- run all tests
