-- Class: display

-- Function: create
-- Parameters:
-- w - Width
-- h - Height
--
-- Returns:
-- Display
function create (w, h) end

-- Function: get_event_source
--
-- Returns:
-- event_source
function get_event_source (display) end

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
function get_backbuffer (display) end

-- Function: get_current
--
-- Returns:
-- current Display
function get_current () end

-- Function: get_flags
--
-- Returns:
-- display flags
function get_flags (display) end

-- Function: get_format
--
-- Returns:
-- current display pixel format
function get_format (display) end

-- Function: get_refresh_rate
--
-- Returns:
-- current display refreshrate
function get_refresh_rate (display) end

-- Function: get_window_position
--
-- Returns:
-- x, y
function get_window_position (display) end

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
function resize (display, width, height) end

-- Function: set_current
-- Parameters:
-- display - Which display to set
--
-- Returns:
-- true on success
function set_current (display) end

-- Function: acknowledge_resize
-- Parameters:
-- display - Which display
--
-- Returns:
-- true on success
function acknowledge_resize (display) end

-- Function: set_icon
-- Parameters:
-- icon - Which bitmap to use
function set_icon (display, icon) end

-- Function: get_option
-- Parameters:
-- display - display
-- option - Which option to get
--
-- Returns:
-- value
function get_option (display, option) end

-- Function: set_window_position
-- Parameters:
-- display - Which display to move
-- x - Position
-- y - Position
function set_window_position (display, x, y) end

-- Function: set_window_title
-- Parameters:
-- title - A string
function set_window_title (display, title) end

-- Function: toggle_flag
-- Parameters:
-- display - Which display
-- flag - FULLSCREEN_WINDOW or ALLEGRO_NOFRAME
-- onoff - toggle
function toggle_flag (display, flag, onoff) end

-- Function: update_region
-- Parameters:
-- x - left
-- y - top
-- width - width
-- height - height
function update_region(x, y, width, height)

-- Function: wait_for_vsync
-- Returns:
-- false if not possible, true if successful.
function wait_for_vsync () end

-- Function: get_num_modes
-- Returns:
-- number of modes available
function get_num_modes () end

-- Function: get_mode
-- Parameters:
-- index - which mode
--
-- Returns:
-- nil on failure. On success, a table containing the values for width, height, format and refresh_rate
function get_mode (index) end

-- Function: get_num_video_adapters
-- Returns:
-- the number of video "adapters" attached to the computer.
function get_num_video_adapters () end

-- Function: get_monitor_info
-- Parameters:
-- adapter - adapter index
--
-- Returns:
-- a table containing the values for monitor position on the desktop: x1, y1, x2, y2
function get_monitor_info (adapter) end

-- Function: get_height
-- Returns:
-- Height of current display
function get_height (display) end

-- Function: get_width
-- Returns:
-- Width of current display
function get_width (display) end

-- List: Events
-- EVENT_CLOSE - The close button of the window has been pressed.
-- EVENT_SWITCH_OUT - The window is no longer active, that is the user might have clicked into another window or "tabbed" away.
-- EVENT_RESIZE - The window has been resized. Fields: x, y, width, height

-- List: Display flags
-- WINDOWED - Windowed mode
-- FULLSCREEN - Fullscreen mode
-- RESIZABLE - Allow resizing
-- OPENGL - opengl
-- DIRECT3D - d3d, not yet supported (allua so far only developed using Linux)
-- NOFRAME - no frame
-- FULLSCREEN_WINDOW

-- List: display options
-- RED_SIZE - ALLEGRO_RED_SIZE
-- GREEN_SIZE - ALLEGRO_GREEN_SIZE
-- BLUE_SIZE - ALLEGRO_BLUE_SIZE
-- ALPHA_SIZE - ALLEGRO_ALPHA_SIZE
-- COLOR_SIZE - ALLEGRO_COLOR_SIZE
-- RED_SHIFT - ALLEGRO_RED_SHIFT
-- GREEN_SHIFT - ALLEGRO_GREEN_SHIFT
-- BLUE_SHIFT - ALLEGRO_BLUE_SHIFT
-- ALPHA_SHIFT - ALLEGRO_ALPHA_SHIFT
-- ACC_RED_SIZE - ALLEGRO_ACC_RED_SIZE
-- ACC_GREEN_SIZE - ALLEGRO_ACC_GREEN_SIZE
-- ACC_BLUE_SIZE - ALLEGRO_ACC_BLUE_SIZE
-- ACC_ALPHA_SIZE - ALLEGRO_ACC_ALPHA_SIZE
-- STEREO - ALLEGRO_STEREO
-- AUX_BUFFERS - ALLEGRO_AUX_BUFFERS
-- DEPTH_SIZE - ALLEGRO_DEPTH_SIZE
-- STENCIL_SIZE - ALLEGRO_STENCIL_SIZE
-- SAMPLE_BUFFERS - ALLEGRO_SAMPLE_BUFFERS
-- SAMPLES - ALLEGRO_SAMPLES
-- RENDER_METHOD - ALLEGRO_RENDER_METHOD
-- FLOAT_COLOR - ALLEGRO_FLOAT_COLOR
-- FLOAT_DEPTH - ALLEGRO_FLOAT_DEPTH
-- SINGLE_BUFFER - ALLEGRO_SINGLE_BUFFER
-- SWAP_METHOD - ALLEGRO_SWAP_METHOD
-- COMPATIBLE_DISPLAY - ALLEGRO_COMPATIBLE_DISPLAY
-- UPDATE_DISPLAY_REGION - ALLEGRO_UPDATE_DISPLAY_REGION
-- VSYNC - ALLEGRO_VSYNC

-- List: Option importance
-- REQUIRE - ALLEGRO_REQUIRE
-- SUGGEST - ALLEGRO_SUGGEST
-- DONTCARE - ALLEGRO_DONTCARE
