-- Class: bitmap

-- Function: init_image_addon
-- Returns:
-- true on success, false on failure
function init_image_addon () end

-- Function: clone
-- Parameters:
-- bitmap - bitmap to clone
--
-- Returns:
-- clone of bitmap
function clone (bitmap) end

-- Function: create
-- Parameters:
-- w - Width of bitmap
-- h - Height of bitmap
--
-- Returns:
-- Bitmap instance
function create (w, h) end

-- Function: create_sub
-- Parameters:
-- parent - Parent bitmap
-- x - Left edge
-- y - Top edge
-- w - Width of bitmap
-- h - Height of bitmap
--
-- Returns:
-- Bitmap instance
function create_sub (parent, x, y, w, h) end

-- Function: get_new_flags
-- Returns:
-- flags
function get_new_flags () end

-- Function: set_new_flags
-- Parameters:
-- flags - flags
function set_new_flags (flags) end

-- Function: get_new_format
-- Returns:
-- format
function get_new_format () end

-- Function: set_new_format
-- Parameters:
-- format - format
function set_new_format (format) end

-- Function: load
-- Parameters:
-- filename - path to file
--
-- Returns:
-- Bitmap instance
function load (filename) end

-- Function: save
-- Parameters:
-- bitmap - image to save
-- filename - path to file
--
-- Returns:
-- true on success, false on failure
function save (bitmap, filename) end

-- Function: get_flags
-- Parameters:
-- bitmap - bitmap
--
-- Returns:
-- flags
function get_flags (bitmap) end

-- Function: get_format
-- Parameters:
-- bitmap - bitmap
--
-- Returns:
-- format
function get_format (bitmap) end

-- Function: get_width
-- Parameters:
-- bitmap - bitmap
--
-- Returns:
-- Width of bitmap
function get_width (bitmap) end

-- Function: get_height
-- Parameters:
-- bitmap - bitmap
--
-- Returns:
-- Height of bitmap
function get_height (bitmap) end

-- Function: get_pixel
-- Parameters:
-- bitmap - bitmap
-- x - position
-- y - position
--
-- Returns:
-- color
function get_pixel (bitmap, x, y) end

-- Function: is_locked
-- Parameters:
-- bitmap - bitmap
--
-- Returns:
-- true if bitmap is locked, otherwise false.
function is_locked (bitmap) end

-- Function: is_compatible
-- Parameters:
-- bitmap - bitmap
--
-- Returns:
-- true if bitmap is compatible, otherwise false.
function is_compatible (bitmap) end

-- Function: is_sub
-- Parameters:
-- bitmap - bitmap
--
-- Returns:
-- true if bitmap is a sub bitmap, otherwise false.
function is_sub (bitmap) end

-- Function: clear_to_color
-- Parameters:
-- color - color
function clear_to_color (color) end

-- Function: draw
-- Parameters:
-- bitmap - bitmap
-- x - Left position
-- y - Top position
-- flags - Bitmap flags
function draw (bitmap, x, y, flags) end

-- Function: draw_region
-- Parameters:
-- bitmap - bitmap
-- sx - Source Left
-- sy - Source Top
-- sw - Source width
-- sh - Source height
-- dx - Left position
-- dy - Top position
-- flags - Bitmap flags
function draw_region (bitmap, sx, sy, sw, sh, dx, dy, flags) end

-- Function: draw_rotated
-- Parameters:
-- bitmap - bitmap
-- cx - Source Center x
-- cy - Source Center y
-- dx - Left position
-- dy - Top position
-- angle - Rotation
-- flags - Bitmap flags
function draw_rotated (bitmap, cx, cy, dx, dy, angle, flags) end

-- Function: draw_scaled_rotated
-- Parameters:
-- bitmap - bitmap
-- cx - Source Center x
-- cy - Source Center y
-- dx - Left position
-- dy - Top position
-- scalex - Scale x-wise
-- scaley - Scale y-wise
-- angle - Rotation
-- flags - Bitmap flags
function draw_scaled_rotated (bitmap, cx, cy, dx, dy, scalex, scaley, angle, flags) end

-- Function: draw_scaled
-- Parameters:
-- bitmap - bitmap
-- sx - Source Left
-- sy - Source Top
-- sw - Source width
-- sh - Source height
-- dx - Destination Left
-- dy - Destination Top
-- dw - Destination width
-- dh - Destination height
-- flags - Bitmap flags
function draw_scaled (bitmap, sx, sy, sw, sh, dx, dy, dw, dh, flags) end

-- Function: get_target
-- Returns:
-- current target bitmap
function get_target () end

-- Function: set_target
-- Parameters:
-- bitmap - bitmap
function set_target (bitmap) end

-- Function: get_clipping_rectangle
-- Returns:
-- x, y, w, h
function get_clipping_rectangle () end

-- Function: set_clipping_rectangle
-- Parameters:
-- x - x
-- y - y
-- w - w
-- h - h
function set_clipping_rectangle (x, y, w, h) end

-- Function: convert_mask_to_alpha
-- Parameters:
-- bitmap - bitmap
-- mask_color - color
function convert_mask_to_alpha (bitmap, color) end

-- List: flags
-- FLIP_HORIZONTAL
-- FLIP_VERTICAL
-- MEMORY_BITMAP
-- KEEP_BITMAP_FORMAT
-- FORCE_LOCKING
-- NO_PRESERVE_TEXTURE
