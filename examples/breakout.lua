--[[ Breakout
14*14 blocks
full width, height down to half playfield.
--]]

require('liballua')

allegro5.init()
allegro5.keyboard.install()
allegro5.mouse.install()
allegro5.bitmap.init_image_addon ()
allegro5.font.init_addon()
allegro5.font.init_ttf_addon()
allegro5.primitives.init_addon()

display = allegro5.display.create(800, 600, allegro5.display.WINDOWED)
event_queue = allegro5.event_queue.create()

event_queue:register_event_source(display:get_event_source())
keyboard = allegro5.keyboard.get_event_source()
event_queue:register_event_source(keyboard)
mouse = allegro5.mouse.get_event_source()
event_queue:register_event_source(mouse)

font = allegro5.font.load_ttf("data/times.ttf", 16, 0)

vector2 = {}
vector2.create = function(x, y)
	rt = {}
	rt.x = x
	rt.y = y
	return rt
end

vector2.increment = function(a, b)
	a.x = a.x + b.x
	a.y = a.y + b.y
end

vector2.mult_scalar = function(a, s)
	r = {}
	r.x = a.x * s
	r.y = a.y * s
	return r
end

brick_image = allegro5.bitmap.load("data/brick.png")

initiate_bricks = function()
	bricks = {}
	for x = 0, 13 do
		bricks[x] = {}
	end
end

set_up_level1 = function()
	initiate_bricks()
	for x = 0, 13 do
		for y = 0, 13 do
			bricks[x][y] = {}
			bricks[x][y].color = allegro5.color.map_rgba(math.random(255), math.random(255), math.random(255), 127)
		end
	end
end

draw_bricks = function()
	dw = display:get_width()
	dh = display:get_height()
	bw = math.floor(dw/14)
	bh = math.floor(dh/28)
	light = allegro5.color.map_rgba(255, 255, 255, 127)
	dark = allegro5.color.map_rgba(0, 0, 0, 127)
	for x = 0, 13 do
		for y = 0, 13 do
			brick = bricks[x][y]
			if brick then
				top = y*bh
				left = x*bw
				bottom = y*bh+bh-1
				right = x*bw+bw-1
				brick_image:draw_scaled(0, 0, brick_image:get_width(), brick_image:get_height(), left, top, bw, bh, 0)
				allegro5.primitives.draw_filled_rectangle(left, top, right, bottom, brick.color)
			end
		end
	end
end

balls = {}
ball_image = allegro5.bitmap.load("data/ball.png")

create_ball = function(pos, vel)
	ball = {}
	ball.pos = pos
	ball.vel = vel
	table.insert(balls, ball)
end

update_balls = function(dt)
	for k, v in pairs(balls) do
		old_pos = {x = v.pos.x, y = v.pos.y}
		vector2.increment (v.pos, vector2.mult_scalar (v.vel, dt))
		-- Collision with playfield edges
		if v.pos.x < 0 or v.pos.x > 800 then
			v.vel.x = -v.vel.x
		end
		if v.pos.y < 0 then
			v.vel.y = -v.vel.y
		end
		-- Collision with envelope
		if v.pos.y > 580 and v.pos.x > player.position.x - player.width/2 and v.pos.x < player.position.x + player.width/2 then
			-- Todo: angle depending on where it hits the envelope
			v.vel.y = -v.vel.y
		end
		-- Collision with brick
		dw = display:get_width()
		dh = display:get_height()
		bw = math.floor(dw/14)
		bh = math.floor(dh/28)

		brick_x = math.floor(v.pos.x / bw)
		brick_y = math.floor(v.pos.y / bh)

		if brick_x > 13 then brick_x = 13 end
		if brick_x < 0 then brick_x = 0 end
		
		if brick_y < 14 and bricks[brick_x][brick_y] then
			-- Todo: proper handling monday has some rect/circle collision
			if old_pos.y > brick_y * bh or old_pos.y < brick_y * bh then
				bricks[brick_x][brick_y] = nil
				v.vel.y = -v.vel.y
			elseif old_pos.x > brick_x * bw or old_pos.x < brick_x * bw then
				bricks[brick_x][brick_y] = nil
				v.vel.x = -v.vel.x
			end
		end
		
		vector2.increment (v.pos, vector2.mult_scalar (v.vel, dt))
	end
end

draw_balls = function()
	for k, v in pairs(balls) do
		ball_image:draw(v.pos.x, v.pos.y, 0)
	end
end

player = {}
player.image = allegro5.bitmap.load("data/envelope.png")
player.position = vector2.create(400, 600)
player.velocity = 1000
player.fire = false
player.angle = 0
player.width = 100

player.update = function(dt)
	if mouse.x > player.position.x then
		player.position.x = player.position.x + player.velocity * dt
	end
	if mouse.x < player.position.x then
		player.position.x = player.position.x - player.velocity * dt
	end
end

player.draw = function()
	cx = player.image:get_width() / 2
	cy = player.image:get_height() / 2
	px = player.position.x
	py = player.position.y
	player.image:draw_rotated(cx, cy, px, py - cy, player.angle, 0)
end

main = function()
	time_previous = allegro5.current_time()
	accumulated_time = 0
	frames = 0
	set_up_level1 ()

	mouse = {}
	mouse.x = 0

	create_ball (vector2.create (400, 300), vector2.create (100, -100))

	while not quit do
		event = event_queue:get_next_event()
		if event.type == allegro5.display.EVENT_CLOSE or event.type == allegro5.keyboard.EVENT_DOWN and event.keycode == allegro5.keyboard.KEY_ESCAPE then
			quit = true
		end
		
		if event.type == allegro5.mouse.EVENT_AXES then
			mouse.x = event.x
		end

		time_now = allegro5.current_time()
		dt = time_now - time_previous
		time_previous = time_now
		accumulated_time = accumulated_time + dt

		dt = .01
		if accumulated_time > dt then
			accumulated_time = accumulated_time - dt
			update_balls (dt)
			player.update (dt)

			draw_bricks ()
			draw_balls ()
			player.draw ()

			allegro5.display.flip()
			allegro5.bitmap.clear_to_color(allegro5.color.map_rgba(0, 0, 0, 0))
		end

		allegro5.rest(0.001)
		frames = frames + 1
	end
end

main()

print("Frames per second ", frames / allegro5.current_time())
