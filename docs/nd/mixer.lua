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

-- Function: attach_voice
-- Parameters:
--
-- Returns:
-- success
function attach_mixer (mixer, voice) end

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

-- Function: get_channels
-- Parameters:
--
-- Returns:
-- channel conf
function get_channels (mixer) end

-- Function: get_depth
-- Parameters:
--
-- Returns:
-- depth
function get_depth (mixer) end

-- Function: get_quality
-- Parameters:
--
-- Returns:
-- quality
function get_quality (mixer) end

-- Function: set_quality
-- Parameters:
--
-- Returns:
-- success
function set_quality (mixer, val) end

-- Function: get_playing
-- Parameters:
--
-- Returns:
-- playing
function get_playing (mixer) end

-- Function: set_playing
-- Parameters:
--
-- Returns:
-- success
function set_playing (mixer, val) end

-- Function: get_attached
-- Parameters:
--
-- Returns:
-- attached
function get_attached (mixer) end

-- Function: detach
-- Parameters:
--
-- Returns:
-- success
function detach (mixer) end
