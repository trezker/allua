--[[
Allua demo game - Naturoids
Player control a bumblebee, classic asteroids style.
Leafs whirl around, threatening to destabilise your flight.
]]--

leaf_max_speed = 20

allegro5.init()
display = allegro5.Display.new(640, 480, allegro5.Display.WINDOWED)
event_queue = allegro5.Event_queue.new()

event_queue:register_event_source(display)
keyboard = allegro5.Keyboard.get()
event_queue:register_event_source(keyboard)
mouse = allegro5.Mouse.get()
event_queue:register_event_source(mouse)

leaf = allegro5.Bitmap.load("data/green_leaf.png")
stinger = allegro5.Bitmap.load("data/stinger.png")
bumblebee = allegro5.Bitmap.load("data/bumblebee.png")

font = allegro5.Font.load_ttf("data/times.ttf", 16, 0)

mouse_x = 0
mouse_y = 0
mouse_z = 0
mouse_b = {}

player = {}
player.x = 320
player.y = 240
player.vx = 0
player.vy = 0
player.angle = 0
player.fire_time = 0
player.image = bumblebee

leafs = {}
stingers = {}

Screenwrap = function(self)
	width = allegro5.Display.width()
	height = allegro5.Display.height()
	if self.x<0 then self.x = self.x + width end
	if self.x>width then self.x = self.x - width end
	if self.y<0 then self.y = self.y + height end
	if self.y>height then self.y = self.y - height end
end

Draw_object = function(self)
	cx = self.image:width()/2
	cy = self.image:height()/2
	self.image:draw_rotated(cx, cy, self.x, self.y, self.angle, 0)
end

Update_moving_object = function(self)
	self.x = self.x + self.vx * dt
	self.y = self.y + self.vy * dt
	Screenwrap(self)
end

-- Leaf functions

Update_leaf = function(self, dt)
	Update_moving_object(self)

	self.vangle = self.vangle + (math.random() - .5) * dt
	self.angle = self.angle + self.vangle * dt
end

Create_leaf = function()
	new = {}

	new.x = math.random(0, 640)
	new.y = 0
	new.vx = math.random(-leaf_max_speed, leaf_max_speed)
	new.vy = math.random(-leaf_max_speed, leaf_max_speed)
	new.angle = math.random() * math.pi * 2
	new.vangle = math.random() - .5

	new.update = Update_leaf
	new.draw = Draw_object
	new.image = leaf
	return new
end

-- Stinger functions
Update_stinger = function(self, dt)
	Update_moving_object(self)
end

Create_stinger = function()
	new = {}

	new.x = player.x
	new.y = player.y
	new.vx = math.cos(-player.angle) * 500
	new.vy = math.sin(-player.angle) * 500
	new.angle = player.angle

	new.update = Update_stinger
	new.draw = Draw_object
	new.image = stinger
	return new
end

time_previous = allegro5.current_time()
leaf_spawn_time = 0

while not quit do
	event = event_queue:get_next_event()
	if event.type == allegro5.Display.EVENT_CLOSE or event.type == allegro5.Keyboard.EVENT_DOWN and event.keycode == allegro5.Keyboard.KEY_ESCAPE then
		quit = true
	end

	if event.type == allegro5.Mouse.EVENT_AXES then
		mouse_x = event.x
		mouse_y = event.y
		mouse_z = event.z
	end

	if event.type == allegro5.Mouse.EVENT_DOWN then
		mouse_b[event.button] = true
	end
	if event.type == allegro5.Mouse.EVENT_UP then
		mouse_b[event.button] = false
	end

	if event.type == allegro5.Keyboard.EVENT_DOWN then
		if event.keycode == allegro5.Keyboard.KEY_LEFT then
			player.turn_left = true
		end
		if event.keycode == allegro5.Keyboard.KEY_RIGHT then
			player.turn_right = true
		end
		if event.keycode == allegro5.Keyboard.KEY_UP then
			player.move_forward = true
		end
		if event.keycode == allegro5.Keyboard.KEY_DOWN then
			player.move_reverse = true
		end
		if event.keycode == allegro5.Keyboard.KEY_SPACE then
			player.firing = true
		end
	end

	if event.type == allegro5.Keyboard.EVENT_UP then
		if event.keycode == allegro5.Keyboard.KEY_LEFT then
			player.turn_left = false
		end
		if event.keycode == allegro5.Keyboard.KEY_RIGHT then
			player.turn_right = false
		end
		if event.keycode == allegro5.Keyboard.KEY_UP then
			player.move_forward = false
		end
		if event.keycode == allegro5.Keyboard.KEY_DOWN then
			player.move_reverse = false
		end
		if event.keycode == allegro5.Keyboard.KEY_SPACE then
			player.firing = false
			player.fire_time = 0
		end
	end

	time_now = allegro5.current_time()
	dt = time_now - time_previous
	time_previous = time_now

	leaf_spawn_time = leaf_spawn_time - dt
	if leaf_spawn_time <= 0 then
		table.insert(leafs, Create_leaf())
		leaf_spawn_time = leaf_spawn_time +1
	end

	for i,v in ipairs(leafs) do 
		v:update(dt)
	end

	for i,v in ipairs(stingers) do 
		v:update(dt)
	end
	
	if player.turn_left then
		player.angle = player.angle + 5 * dt
	end
	if player.turn_right then
		player.angle = player.angle - 5 * dt
	end
	if player.move_forward then
		player.vx = player.vx + math.cos(-player.angle) * 1000 * dt
		player.vy = player.vy + math.sin(-player.angle) * 1000 * dt
		player.vx = player.vx * .999
		player.vy = player.vy * .999
	end
	if player.move_reverse then
		player.vx = player.vx - math.cos(-player.angle) * 700 * dt
		player.vy = player.vy - math.sin(-player.angle) * 700 * dt
		player.vx = player.vx * .999
		player.vy = player.vy * .999
	end
	if player.firing then
		if player.fire_time <= 0 then
			player.fire_time = 1
			table.insert(stingers, Create_stinger())
		end
		player.fire_time = player.fire_time -dt
	end

	Update_moving_object (player)
	
	for i,v in ipairs(leafs) do 
		v:draw()
	end

	for i,v in ipairs(stingers) do 
		v:draw()
	end

	Draw_object(player)

	allegro5.Display.flip()
	allegro5.Display.clear(allegro5.Color.map_rgba(0, 0, 0, 0))
	allegro5.rest(0.001)
end
