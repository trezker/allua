-- Class: font

-- Function: load_ttf
-- Parameters:
-- filename - Path to ttf font
-- size - Size
-- options - Options
--
-- Returns:
-- Font on success, nil on failure
function load_ttf (filename, size, options) end

-- Function: load_bitmap
-- Parameters:
-- filename - Path to bitmap font
--
-- Returns:
-- Font on success, nil on failure
function load_bitmap (filename) end

-- Function: draw_text
-- Parameters:
-- font - Font to render with
-- x - Horizontal position
-- y - Vertical position
-- flags - flags
-- text - The text
function draw_text (font, x, y, flags, text) end
