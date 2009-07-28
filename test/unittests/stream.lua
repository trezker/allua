Test_stream = {}

function Test_stream:test01_prepare()
	allegro5.init()
	allegro5.audio.install(allegro5.audio.AUDIO_DRIVER_AUTODETECT)
	allegro5.audio.reserve_samples(2)
end

function Test_stream:test02_create()
	stream = allegro5.stream.from_file (2, 2, "data/powerup.ogg");
	assertEquals("stream", tostring(stream):sub(1, 6))
end

function Test_stream:test10_cleanup()
	stream = nil
	collectgarbage()
end
