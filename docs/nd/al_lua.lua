-- Namespace: allegro5

-- Function: init
-- Initiates allegro
-- Temporarily, this function installs and inits a whole bunch of stuff. That's why mouse and keyboard among other things don't have init/install functions, yet.
function init () end

-- Function: current_time
-- Returns:
-- Current time.
function current_time () end

-- Function: rest
-- This is recommended to call regularly, it helps making your program run more smoothly on some systems.
-- Parameters:
-- t - Time to rest.
function rest (t) end
