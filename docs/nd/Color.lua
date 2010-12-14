-- Class: color

-- Function: map_rgb
-- Parameters:
-- r - red component
-- g - green component
-- b - blue component
--
-- Returns:
-- A color mapped from the input
function map_rgb (r, g, b) end

-- Function: map_rgb_f
-- Parameters:
-- r - red component
-- g - green component
-- b - blue component
--
-- Returns:
-- A color mapped from the input
function map_rgb_f (r, g, b) end

-- Function: map_rgba
-- Parameters:
-- r - red component
-- g - green component
-- b - blue component
-- a - alpha component
--
-- Returns:
-- A color mapped from the input
function map_rgba (r, g, b, a) end

-- Function: map_rgba_f
-- Parameters:
-- r - red component
-- g - green component
-- b - blue component
-- a - alpha component
--
-- Returns:
-- A color mapped from the input
function map_rgba_f (r, g, b, a) end

-- Function: unmap_rgb
-- Parameters:
-- color - color to unmap
--
-- Returns:
-- r - red component
-- g - green component
-- b - blue component
function unmap_rgb () end

-- Function: unmap_rgb_f
-- Parameters:
-- color - color to unmap
--
-- Returns:
-- r - red component
-- g - green component
-- b - blue component
function unmap_rgb_f () end

-- Function: unmap_rgba
-- Parameters:
-- color - color to unmap
--
-- Returns:
-- r - red component
-- g - green component
-- b - blue component
-- a - alpha component
function unmap_rgba () end

-- Function: unmap_rgba_f
-- Parameters:
-- color - color to unmap
--
-- Returns:
-- r - red component
-- g - green component
-- b - blue component
-- a - alpha component
function unmap_rgba_f () end

-- Function: put_pixel
-- Parameters:
-- color - Color
-- x - Horizontal position
-- y - Vertical position
function put_pixel (color, x, y) end

-- Function: draw_pixel
-- Parameters:
-- color - Color
-- x - Horizontal position
-- y - Vertical position
function draw_pixel (color, x, y) end

-- Function: clear_backbuffer
-- This is the al_clear_to_color function.
-- Since it only takes a color argument it's practical to have in the color class.
--
-- Parameters:
-- color - Color
function clear_backbuffer (color) end

-- Function: set_blender
--
-- Parameters:
-- op - blend
-- src - source
-- dst - destination
function set_blender (op, src, dest) end

-- List: blend
-- ZERO
-- ONE
-- ALPHA
-- INVERSE_ALPHA
-- ADD
-- DEST_MINUS_SRC
-- SRC_MINUS_DEST
