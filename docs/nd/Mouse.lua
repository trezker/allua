-- Class: mouse

-- Function: install
-- Returns:
-- true if successful. If a driver was already installed, nothing happens and true is returned.
function install () end

-- Function: is_installed
function is_installed () end

-- Function: get
-- Returns:
-- Handle to the Mouse
function get () end

-- Function: get_cursor_position
-- Returns:
-- On success x, y. Otherwise nil.
function get_cursor_position () end

-- Function: get_num_axes
-- Returns:
-- Number of movement axes on the mouse
function get_num_axes () end

-- Function: get_num_buttons
-- Returns:
-- Number of buttons on the mouse
function get_num_buttons () end

-- Function: hide_cursor
-- Returns:
-- true on success, false on failure
function hide_cursor () end

-- Function: set_axis
-- Parameters:
-- which - which axis
-- value - value
--
-- Returns:
-- true on success, false on failure
function set_axis (which, value) end

-- Function: set_range
-- Parameters:
-- x1 - left
-- y1 - top
-- x2 - right
-- y2 - bottom
--
-- Returns:
-- true on success, false on failure
function set_range (x1, y1, x2, y2) end

-- List: Events
-- EVENT_AXES - one or more mouse axis values changed. Fields: x, y, z, dx, dy, dz.
-- EVENT_BUTTON_DOWN - a mouse button was pressed. Fields: x, y, z, button.
-- EVENT_BUTTON_UP - a mouse button was released. Fields: x, y, z, button.
-- EVENT_ENTER_DISPLAY - the mouse cursor entered a window opened by the program. Fields: x, y, z.
-- EVENT_LEAVE_DISPLAY - the mouse cursor leave the boundaries of a window opened by the program. Fields: x, y, z.
