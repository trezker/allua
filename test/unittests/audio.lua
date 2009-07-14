Test_audio = {}

allegro5.init()

function Test_audio:test01_functions()
	allegro5.audio.install (allegro5.audio.AUDIO_DRIVER_AUTODETECT)
end
