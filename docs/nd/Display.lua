-- Class: display

-- Function: create
-- Parameters:
-- w - Width
-- h - Height
--
-- Returns:
-- Display
function create (w, h) end

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

-- Function: reset_new_options
-- Undoes all set options
function reset_new_options() end

-- Function: set_new_flags
-- Parameters:
-- flags - new display flags
function set_new_flags(flags) end

-- Function: set_new_refresh_rate
-- Parameters:
-- refresh_rate - new display refresh rate
function set_new_refresh_rate(refresh_rate) end

-- Function: set_new_window_position
-- Parameters:
-- x - horizontal position
-- y - vertical position
function set_new_window_position(x, y) end

-- Function: flip
-- Flips current display.
function flip () end

-- Function: get_backbuffer
--
-- Returns:
-- backbuffer Bitmap
function get_backbuffer () end

-- Function: get_current
--
-- Returns:
-- current Display
function get_current () end

-- Function: get_flags
--
-- Returns:
-- display flags
function get_flags () end

-- Function: get_format
--
-- Returns:
-- current display pixel format
function get_format () end

-- Function: get_refresh_rate
--
-- Returns:
-- current display refreshrate
function get_refresh_rate () end

-- Function: get_frontbuffer
--
-- Returns:
-- frontbuffer Bitmap

function get_frontbuffer () end

-- Function: get_window_position
--
-- Returns:
-- x, y
function get_window_position () end

-- Function: inhibit_screensaver
--
-- Parameters:
-- inhibit - stop the system screensaver from starting up if true is passed, or resets the system back to the default state (the state at program start) if false is passed
--
-- Returns:
-- true if the state was set successfully, otherwise false
function inhibit_screensaver (inhibit) end

-- Function: resize
--
-- Parameters:
-- width - new width of display
-- height - new height of display
--
-- Returns:
-- true on success, or false on error
function resize (width, height) end

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

-- Function: set_icon
-- Parameters:
-- icon - Which bitmap to use
function set_icon (icon) end

-- Function: get_height
-- Returns:
-- Height of current display
function get_height () end

-- Function: get_width
-- Returns:
-- Width of current display
function get_width () end

-- Function: clear
-- Clears current display
function clear () end

-- Function: draw_pixel
-- Parameters:
-- x - Horizonal position
-- y - Vertical position
-- color - Color
function draw_pixel (x, y, color) end


-- List: Events
-- EVENT_CLOSE - The close button of the window has been pressed.
-- EVENT_SWITCH_OUT - The window is no longer active, that is the user might have clicked into another window or "tabbed" away.
-- EVENT_RESIZE - The window has been resized. Fields: x, y, width, height

-- List: Display flags
-- WINDOWED - Windowed mode
-- FULLSCREEN - Fullscreen mode
-- RESIZABLE - Allow resizing
