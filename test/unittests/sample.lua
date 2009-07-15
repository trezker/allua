Test_sample = {}



function Test_sample:test01_prepare()
	allegro5.init()
	allegro5.audio.install(allegro5.audio.AUDIO_DRIVER_AUTODETECT)
	allegro5.audio.reserve_samples(2)
end

function Test_sample:test02_load()
	sample = allegro5.sample.load("data/powerup.ogg")
	assertEquals("sample", tostring(sample):sub(1, 6))
end
