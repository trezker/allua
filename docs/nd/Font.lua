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

-- Function: load_image
-- Parameters:
-- filename - Path to ttf font
--
-- Returns:
-- Font
function load_image (filename) end

-- Function: textout
-- Parameters:
-- font - Font to render with
-- x - Horizontal position
-- y - Vertical position
-- text - The text
-- chars - Number of characters to actually render
function textout (font, x, y, text, chars) end
