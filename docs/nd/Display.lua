-- Class: Display

-- Function: create
-- Parameters:
-- x - Width
-- y - Height
-- flags - Display flags
--
-- Returns:
-- Display
function create (x, y, flags) end

-- Function: get_num_display_formats
--
-- Returns:
-- Number of available display formats
function get_num_display_formats () end

-- Function: get_format_option
--
-- Parameters:
-- i - Which display format
-- option - Which option to look at
--
-- Returns:
-- Value of the option
function get_format_option (i, option) end

-- Function: set_new_format
--
-- Parameters:
-- i - Which display format
function set_new_format (i) end

-- Function: get_new_flags
--
-- Returns:
-- Flags set for new display
function get_new_flags () end

-- Function: get_new_refresh_rate
--
-- Returns:
-- Refresh rate set for new display
function get_new_refresh_rate () end

-- Function: get_new_window_position
--
-- Returns:
-- x and y position for new display
function get_new_window_position() end

-- Function: set_new_option
--
-- Parameters:
-- option - Option
-- value - Option value
-- importance - How important the option is
function set_new_option(option, value, importance) end

-- Function: get_new_option
--
-- Parameters:
-- option - Option
--
-- Returns:
-- value and importance of the option
function get_new_option(option) end

-- Function: flip
-- Flips current display.
function flip () end

-- Function: set_current
-- Parameters:
-- display - Which display to set
--
-- Returns:
-- true on success
function set_current (display) end

-- Function: acknowledge_resize
-- Parameters:
-- display - Which display to set
--
-- Returns:
-- true on success
function acknowledge_resize (display) end

-- Function: clear
-- Clears current display
function clear () end

-- Function: draw_pixel
-- Parameters:
-- x - Horizonal position
-- y - Vertical position
-- color - Color
function draw_pixel (x, y, color) end

-- Function: height
-- Returns:
-- Height of current display
function height () end

-- Function: width
-- Returns:
-- Width of current display
function width () end

-- List: Events
-- EVENT_CLOSE - The close button of the window has been pressed.
-- EVENT_SWITCH_OUT - The window is no longer active, that is the user might have clicked into another window or "tabbed" away.
-- EVENT_RESIZE - The window has been resized. Fields: x, y, width, height

-- List: Display flags
-- WINDOWED - Windowed mode
-- FULLSCREEN - Fullscreen mode
-- RESIZABLE - Allow resizing
