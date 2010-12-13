-- Class: audio

-- Function: install
--
-- Returns:
-- true on success, false on failure
function install () end

-- Function: uninstall
function uninstall () end

-- Function: reserve_samples
-- Parameters:
-- reserve_samples - number of samples
--
-- Returns:
-- true on success, false on failure
function install (reserve_samples) end

-- Function: init_acodec_addon
--
-- Returns:
-- success
function init_acodec_addon () end

--List: depths
-- AUDIO_DEPTH_INT8
-- AUDIO_DEPTH_INT16
-- AUDIO_DEPTH_INT24
-- AUDIO_DEPTH_FLOAT32
-- AUDIO_DEPTH_UNSIGNED
-- AUDIO_DEPTH_UINT8
-- AUDIO_DEPTH_UINT16
-- AUDIO_DEPTH_UINT24

--List: channels
-- CHANNEL_CONF_1
-- CHANNEL_CONF_2
-- CHANNEL_CONF_3
-- CHANNEL_CONF_4
-- CHANNEL_CONF_5_1
-- CHANNEL_CONF_6_1
-- CHANNEL_CONF_7_1

--List: playmode
-- PLAYMODE_ONCE
-- PLAYMODE_LOOP
-- PLAYMODE_BIDIR

--List: mixer quality
-- MIXER_QUALITY_POINT
-- MIXER_QUALITY_LINEAR
