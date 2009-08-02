Test_audio = {}

function Test_audio:test00_prepare()
	allegro5.init()
end

function Test_audio:test01_functions()
	install = allegro5.audio.install (allegro5.audio.AUDIO_DRIVER_AUTODETECT)
	reserve = allegro5.audio.reserve_samples (2)
	ogg = allegro5.audio.init_ogg_vorbis_addon()
	allegro5.audio.uninstall ()
	assertEquals("boolean", type(install))
	assertEquals("boolean", type(reserve))
	assertEquals("boolean", type(ogg))
end
