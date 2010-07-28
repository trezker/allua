-- Class: font

-- Function: init_addon
-- Initialises the font addon
function init_addon () end

-- Function: init_ttf_addon
-- Initialises the ttf addon
function init_ttf_addon () end

-- Function: load
-- Parameters:
-- filename - Path to font file
-- size - Size
-- flags - flags
--
-- Returns:
-- Font on success, nil on failure
function load (filename, size, flags) end

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
-- color - color
-- x - Horizontal position
-- y - Vertical position
-- flags - flags
-- text - The text
function draw_text (font, color, x, y, flags, text) end

-- Function: draw_justified_text
-- Parameters:
-- font - Font to render with
-- color - color
-- x1 - Horizontal position begin
-- x2 - Horizontal position end
-- y - Vertical position
-- diff - diff
-- flags - flags
-- text - The text
function draw_justified_text (font, color, x1, x2, y, diff, flags, text) end

-- Function: get_text_dimensions
-- Parameters:
-- font - font
-- text - text
--
-- Returns:
-- bbx - left
-- bby - top
-- bbw - width
-- bbh - height
function get_text_dimensions(font, text) end

-- Function: get_line_height
-- Parameters:
-- font - font
--
-- Returns:
-- height of a line of this font
function get_line_height(font) end

-- Function: get_text_width
-- Parameters:
-- font - font
-- text - text
--
-- Returns:
-- Width of the text drawn with this font
function get_text_width(font, text) end

-- List: Options
-- ALIGN_LEFT
-- ALIGN_CENTRE
-- ALIGN_RIGHT
-- TTF_NO_KERNING

