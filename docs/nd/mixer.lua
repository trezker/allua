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
