-- Class: keyboard

-- Function: install
-- Returns:
-- true if successful. If a driver was already installed, nothing happens and true is returned.
function install () end

-- Function: uninstall
function uninstall () end

-- Function: is_installed
-- Returns:
-- true if keyboard is installed
function is_installed () end

-- Function: get_event_source
--
-- Returns:
-- event_source
function get_event_source () end

-- Function: set_leds
-- Parameters:
-- leds - leds
--
-- Returns:
-- false if the current keyboard driver cannot set LED indicators.
function set_leds (leds) end

-- Function: keycode_to_name
-- Parameters:
-- keycode - Keycode to get a name for
--
-- Returns:
-- name of key
function keycode_to_name (keycode) end

-- Function: keycode_from_name
-- This function is the reverse of keycode_to_name, at the time of its creation allegro had no such function.
-- 
-- Parameters:
-- name - name of key
-- 
-- Returns:
-- keycode
function keycode_from_name (name) end

-- List: Events
-- EVENT_DOWN - a keyboard key was pressed. Fields: keycode, display
-- EVENT_UP - a keyboard key was released. Fields: keycode, display.
-- EVENT_CHAR - a typed character. Fields: keycode, unichar, string, modifiers, repeated, display.
