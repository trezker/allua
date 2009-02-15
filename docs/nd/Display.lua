-- Class: Display

-- Function: new
-- Parameters:
-- x - Width
-- y - Height
-- flags - Display flags
--
-- Returns:
-- Display
function new (x, y, flags) end

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

-- Function: draw_line
-- Parameters:
-- fx - Start x
-- fy - Start y
-- tx - End x
-- ty - End y
-- color - Color
function draw_line (fx, fy, tx, ty, color) end

-- Function: draw_rectangle
-- Parameters:
-- tlx - Top left x
-- tly - Top left y
-- brx - Bottom right x
-- bry - Bottom right y
-- color - Color
-- flags - Flags
function draw_rectangle (tlx, tly, brx, bry, color, flags) end

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