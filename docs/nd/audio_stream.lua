-- Class: audio_stream

-- Function: create
-- Parameters:
--
-- Returns:
-- audio_stream on success, nil on failure
function load (buffer_count, samples, freq, depth, chan_conf) end

-- Function: load
-- Parameters:
--
-- Returns:
-- audio_stream on success, nil on failure
function load (filename, buffer_count, samples) end

-- Function: rewind
-- Parameters:
--
-- Returns:
-- success
function rewind (audio_stream) end

-- Function: get_frequency
-- Parameters:
--
-- Returns:
-- frequency
function get_frequency (audio_stream) end

-- Function: get_channels
-- Parameters:
--
-- Returns:
-- channels
function get_channels (audio_stream) end

-- Function: get_depth
-- Parameters:
--
-- Returns:
-- depth
function get_depth (audio_stream) end

-- Function: get_length
-- Parameters:
--
-- Returns:
-- length
function get_length (audio_stream) end

-- Function: get_speed
-- Parameters:
--
-- Returns:
-- speed
function get_speed (audio_stream) end

-- Function: set_speed
-- Parameters:
--
-- Returns:
-- success
function set_speed (audio_stream, val) end

-- Function: get_gain
-- Parameters:
--
-- Returns:
-- gain
function get_gain (audio_stream) end

-- Function: set_gain
-- Parameters:
--
-- Returns:
-- success
function set_gain (audio_stream, val) end

-- Function: get_pan
-- Parameters:
--
-- Returns:
-- pan
function get_pan (audio_stream) end

-- Function: set_pan
-- Parameters:
--
-- Returns:
-- success
function set_pan (audio_stream, val) end

-- Function: get_playing
-- Parameters:
--
-- Returns:
-- playing
function get_playing (audio_stream) end

-- Function: set_playing
-- Parameters:
--
-- Returns:
-- success
function set_playing (audio_stream, val) end

-- Function: get_playmode
-- Parameters:
--
-- Returns:
-- playmode
function get_playmode (audio_stream) end

-- Function: set_playmode
-- Parameters:
--
-- Returns:
-- success
function set_playmode (audio_stream, val) end

-- Function: get_attached
-- Parameters:
--
-- Returns:
-- attached or not
function get_attached (audio_stream) end

-- Function: detach
-- Parameters:
--
-- Returns:
-- success
function detach (audio_stream) end

-- Function: seek_secs
-- Parameters:
--
-- Returns:
-- success
function seek_secs (audio_stream, time) end

-- Function: get_position_secs
-- Parameters:
--
-- Returns:
-- position
function get_position_secs (audio_stream) end

-- Function: get_length_secs
-- Parameters:
--
-- Returns:
-- length
function get_length_secs (audio_stream) end

-- Function: set_loop_secs
-- Parameters:
--
-- Returns:
-- success
function set_loop_secs (audio_stream, start, end) end
