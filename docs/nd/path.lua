-- Class: path

-- Function: create
-- Parameters:
--
-- Returns:
-- path
function create (path) end

-- Function: create_for_directory
-- Parameters:
--
-- Returns:
-- path
function create_for_directory (path) end

-- Function: clone
-- Parameters:
--
-- Returns:
-- path
function clone (path) end

-- Function: join
-- Parameters:
--
-- Returns:
-- boolean
function join (path) end

-- Function: get_drive
-- Parameters:
--
-- Returns:
-- string
function get_drive (path) end

-- Function: get_num_components
-- Parameters:
--
-- Returns:
-- components
function get_num_components (path) end

-- Function: get_component
-- Parameters:
--
-- Returns:
-- string
function get_component (path) end

-- Function: get_tail
-- Parameters:
--
-- Returns:
-- string
function get_tail (path) end

-- Function: get_filename
-- Parameters:
--
-- Returns:
-- string
function get_filename (path) end

-- Function: get_basename
-- Parameters:
--
-- Returns:
-- string
function get_basename (path) end

-- Function: get_extension
-- Parameters:
--
-- Returns:
-- string
function get_extension (path) end

-- Function: set_drive
-- Parameters:
function set_drive (path, drive) end

-- Function: append_component
-- Parameters:
function append_component (path, component) end

-- Function: insert_component
-- Parameters:
function insert_component (path, i, component) end

-- Function: replace_component
-- Parameters:
function replace_component (path, i, component) end

-- Function: remove_component
-- Parameters:
function remove_component (path, i) end

-- Function: drop_tail
-- Parameters:
function drop_tail (path) end

-- Function: set_filename
-- Parameters:
function set_filename (path) end

-- Function: set_extension
-- Parameters:
--
-- Returns:
-- boolean
function set_extension (path) end

-- Function: get_string
-- Parameters:
--
-- Returns:
-- string
function get_string (path) end

-- Function: make_canonical
-- Parameters:
function make_canonical (path) end

-- List: constants
-- FILEMODE_READ
-- FILEMODE_WRITE
-- FILEMODE_EXECUTE
-- FILEMODE_HIDDEN
-- FILEMODE_ISFILE
-- FILEMODE_ISDIR
