-- Class: mixer

-- Function: create
-- Parameters:
--
-- Returns:
-- mixer on success, nil on failure
function create (freq, depth, chan_conf) end

-- Function: get_default
-- Parameters:
--
-- Returns:
-- mixer on success, nil on failure
function get_default () end

-- Function: set_default
-- Parameters:
--
-- Returns:
-- success
function set_default (mixer) end

-- Function: restore_default
-- Parameters:
--
-- Returns:
-- success
function restore_default () end

-- Function: attach_mixer
-- Parameters:
--
-- Returns:
-- success
function attach_mixer (mixer, stream) end

-- Function: attach_sample
-- Parameters:
--
-- Returns:
-- success
function attach_sample (mixer, sample_instance) end

-- Function: attach_stream
-- Parameters:
--
-- Returns:
-- success
function attach_stream (mixer, stream) end

-- Function: get_frequency
-- Parameters:
--
-- Returns:
-- frequency
function get_frequency (mixer) end

-- Function: set_frequency
-- Parameters:
--
-- Returns:
-- success
function set_frequency (mixer, val) end
