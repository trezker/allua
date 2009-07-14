Test_audio = {}

allegro5.init()

function Test_audio:test01_functions()
	install = allegro5.audio.install (allegro5.audio.AUDIO_DRIVER_AUTODETECT)
	reserve = allegro5.audio.reserve_samples (2)
	allegro5.audio.uninstall ()
	assertEquals("boolean", type(install))
	assertEquals("boolean", type(reserve))
end
