-- Class: sample

-- Function: load
-- Parameters:
--
-- Returns:
-- sample on success, nil on failure
function load (filename) end

-- Function: save
-- Parameters:
--
-- Returns:
-- true on success, false on failure
function save (sample, filename) end

-- Function: play
-- Parameters:
--
-- Returns:
-- success status, and on success also a sample_id
function play (sample, gain, pan, speed, loop) end

-- Function: stop_samples
-- Parameters:
--
-- Returns:
-- 
function stop_samples () end

-- Function: create_instance
-- Parameters:
--
-- Returns:
-- sample_instance on success, nil on failure
function create_instance (sample) end

-- Function: get_channels
-- Parameters:
--
-- Returns:
-- channels
function get_channels (sample) end

-- Function: get_depth
-- Parameters:
--
-- Returns:
-- depth
function get_depth (sample) end

-- Function: get_frequency
-- Parameters:
--
-- Returns:
-- frequency
function get_frequency (sample) end

-- Function: get_length
-- Parameters:
--
-- Returns:
-- length
function get_length (sample) end

-- Class: sample_id

-- Function: stop
-- Parameters:
--
-- Returns:
-- 
function stop (sample_id) end
