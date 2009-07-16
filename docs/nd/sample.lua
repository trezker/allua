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
