-- Class: native_dialog

-- Function: create
-- Parameters:
--
-- Returns:
-- native_dialog on success, nil on failure
function create (initial_path, title, patterns, mode) end

-- Function: show
-- Parameters:
--
-- Returns:
-- 
function show (native_dialog) end

-- Function: get_count
-- Parameters:
--
-- Returns:
-- number of selected files
function get_count (native_dialog) end

-- Function: get_path
-- Parameters:
--
-- Returns:
-- path i
function get_path (native_dialog, i) end
