-- Class: filechooser

-- Function: create
-- Parameters:
--
-- Returns:
-- filechooser on success, nil on failure
function create (initial_path, title, patterns, mode) end

-- Function: show
-- Parameters:
-- filechooser - filechooser
-- display - display
--
-- Returns:
-- 
function show (filechooser, display) end

-- Function: get_count
-- Parameters:
--
-- Returns:
-- number of selected files
function get_count (filechooser) end

-- Function: get_path
-- Parameters:
--
-- Returns:
-- path i
function get_path (filechooser, i) end

-- List: modes
-- FILECHOOSER_FILE_MUST_EXIST
-- FILECHOOSER_SAVE
-- FILECHOOSER_FOLDER
-- FILECHOOSER_PICTURES
-- FILECHOOSER_SHOW_HIDDEN
-- FILECHOOSER_MULTIPLE
