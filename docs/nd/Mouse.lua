-- Class: mouse

-- Function: install
-- Returns:
-- true if successful. If a driver was already installed, nothing happens and true is returned.
function install () end

-- Function: uninstall
function uninstall () end

-- Function: is_installed
function is_installed () end

-- Function: get_event_source
--
-- Returns:
-- event_source
function get_event_source () end

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
-- Parameters:
-- display - display
--
-- Returns:
-- true on success, false on failure
function hide_cursor (display) end

-- Function: show_cursor
-- Parameters:
-- display - display
--
-- Returns:
-- true on success, false on failure
function show_cursor (display) end

-- Function: set_axis
-- Parameters:
-- which - which axis
-- value - value
--
-- Returns:
-- true on success, false on failure
function set_axis (which, value) end

-- Function: set_w
-- Parameters:
-- w - wheel position
--
-- Returns:
-- true on success, false on failure
function set_w (w) end

-- Function: set_z
-- Parameters:
-- z - wheel position
--
-- Returns:
-- true on success, false on failure
function set_z (z) end

-- Function: set_xy
-- Parameters:
-- display - display
-- x - x
-- y - y
--
-- Returns:
-- true on success, false on failure
function set_xy (display, x, y) end

-- List: Events
-- EVENT_AXES - one or more mouse axis values changed. Fields: x, y, z, dx, dy, dz.
-- EVENT_DOWN - a mouse button was pressed. Fields: x, y, z, button.
-- EVENT_UP - a mouse button was released. Fields: x, y, z, button.
-- EVENT_ENTER_DISPLAY - the mouse cursor entered a window opened by the program. Fields: x, y, z.
-- EVENT_LEAVE_DISPLAY - the mouse cursor leave the boundaries of a window opened by the program. Fields: x, y, z.
