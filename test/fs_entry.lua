require('luaunit')
require('liballua')
USE_EXPECTED_ACTUAL_IN_ASSERT_EQUALS = false
assertEqualsDelta = function(expected, actual, delta)
	assert(math.abs(expected-actual)<delta)
end

allegro5.init()

Test_fs_entry = {}

function Test_fs_entry:test00_prepare()
end

function Test_fs_entry:test01_create()
	entry = allegro5.fs_entry.create ("../data/ball.png")
	assertEquals("fs_entry", tostring(entry):sub(1, 8))
end

function Test_fs_entry:test02_get_name()
	entry = allegro5.fs_entry.create ("../data/ball.png")
	path = entry:get_name()
	assertEquals("string", type(path))
end

function Test_fs_entry:test03_update()
	entry = allegro5.fs_entry.create ("../data/ball.png")
	b = entry:update()
	assertEquals("boolean", type(b))
end

function Test_fs_entry:test04_get()
	entry = allegro5.fs_entry.create ("../data/ball.png")
	mode = entry:get_mode()
	atime = entry:get_atime()
	ctime = entry:get_ctime()
	mtime = entry:get_mtime()
	size = entry:get_size()
	assertEquals("number", type(mode))
	assertEquals("number", type(atime))
	assertEquals("number", type(ctime))
	assertEquals("number", type(mtime))
	assertEquals("number", type(size))
end

function Test_fs_entry:test05_info()
	entry = allegro5.fs_entry.create ("../data/ball.png")
	exists = entry:exists()
	assertEquals("boolean", type(exists))
end

function Test_fs_entry:test05_remove()
	entry = allegro5.fs_entry.create ("../data/dummy")
	b = entry:remove()
	assertEquals("boolean", type(b))
end

function Test_fs_entry:test06_directory()
	entry = allegro5.fs_entry.create ("data/")
	open = entry:open_directory()
	entry_read = entry:read_directory()
	close = entry:close_directory()
	assertEquals("boolean", type(open))
	assertEquals("fs_entry", tostring(entry_read):sub(1, 8))
	assertEquals("boolean", type(close))
end

function Test_fs_entry:test05_uninstall()
	entry = nil
	collectgarbage()
end

LuaUnit:run() -- run all tests
