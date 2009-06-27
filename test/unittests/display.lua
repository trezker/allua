Test_display = {}

function Test_display:setUp()
	allegro5.init()
end

function Test_display:test1_create()
	display = allegro5.display.create(800, 600)
	assertEquals("display", tostring(display):sub(1, 7))
end
