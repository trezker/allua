Test_native_dialog = {}

function Test_native_dialog:test01_create()
	native_dialog = allegro5.native_dialog.create ("", "test", "*.*", allegro5.native_dialog.FILECHOOSER_SAVE)
	assertEquals("native_dialog", tostring(native_dialog):sub(1, 13))
end

function Test_native_dialog:test02_show()
	native_dialog:show()
end

function Test_native_dialog:test10_destroy()
	native_dialog = nil
	collectgarbage()
end
