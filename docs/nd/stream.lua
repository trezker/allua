-- Class: stream

-- Function: from_file
-- Parameters:
--
-- Returns:
-- stream on success, nil on failure
function from_file (buffer_count, samples, filename) end

-- Function: rewind
-- Parameters:
--
-- Returns:
-- success
function rewind (stream) end

-- Function: get_frequency
-- Parameters:
--
-- Returns:
-- frequency
function get_frequency (stream) end

-- Function: get_channels
-- Parameters:
--
-- Returns:
-- channels
function get_channels (stream) end

-- Function: get_depth
-- Parameters:
--
-- Returns:
-- depth
function get_depth (stream) end

-- Function: get_length
-- Parameters:
--
-- Returns:
-- length
function get_length (stream) end

-- Function: get_speed
-- Parameters:
--
-- Returns:
-- speed
function get_speed (stream) end

-- Function: set_speed
-- Parameters:
--
-- Returns:
-- success
function set_speed (stream, val) end

-- Function: get_gain
-- Parameters:
--
-- Returns:
-- gain
function get_gain (stream) end

-- Function: set_gain
-- Parameters:
--
-- Returns:
-- success
function set_gain (stream, val) end

-- Function: get_pan
-- Parameters:
--
-- Returns:
-- pan
function get_pan (stream) end

-- Function: set_pan
-- Parameters:
--
-- Returns:
-- success
function set_pan (stream, val) end

-- Function: get_playing
-- Parameters:
--
-- Returns:
-- playing
function get_playing (stream) end

-- Function: set_playing
-- Parameters:
--
-- Returns:
-- success
function set_playing (stream, val) end

-- Function: get_playmode
-- Parameters:
--
-- Returns:
-- playmode
function get_playmode (stream) end

-- Function: set_playmode
-- Parameters:
--
-- Returns:
-- success
function set_playmode (stream, val) end
