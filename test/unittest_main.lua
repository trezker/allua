require('luaunit')

Test_allegro5 = {}

function Test_allegro5:test_init()
	allegro5.init()
end

LuaUnit:run() -- run all tests
