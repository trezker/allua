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

-- List: Events
-- EVENT_AXES - one or more mouse axis values changed. Fields: x, y, z, dx, dy, dz.
-- EVENT_BUTTON_DOWN - a mouse button was pressed. Fields: x, y, z, button.
-- EVENT_BUTTON_UP - a mouse button was released. Fields: x, y, z, button.
-- EVENT_ENTER_DISPLAY - the mouse cursor entered a window opened by the program. Fields: x, y, z.
-- EVENT_LEAVE_DISPLAY - the mouse cursor leave the boundaries of a window opened by the program. Fields: x, y, z.
