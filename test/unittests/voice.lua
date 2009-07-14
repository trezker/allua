Test_voice = {}

allegro5.init()
allegro5.audio.install(allegro5.audio.AUDIO_DRIVER_AUTODETECT)

function Test_voice:test01_create()
	voice = allegro5.voice.create (44100, allegro5.audio.AUDIO_DEPTH_INT8, allegro5.audio.CHANNEL_CONF_2)
	assertEquals("voice", tostring(voice):sub(1, 5))
end
