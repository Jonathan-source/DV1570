package.path = package.path .. ";C:/Dev/DV1570/resources/scripts/?.lua"

math.randomseed(os.time())

raylib = require 'Raylib'

function PlayerMovement()

	local velocity = {x = 0.0,  y = 0.0, z = 0.0}

	if raylib.IsKeyDown(Keys.KEY_W) then
		velocity.z = 1.0;
	end

	if raylib.IsKeyDown(Keys.KEY_A) then
		velocity.x = 1.0;
	end

	if raylib.IsKeyDown(Keys.KEY_S) then
		velocity.z = -1.0;
	end

	if raylib.IsKeyDown(Keys.KEY_D) then
		velocity.x = -1.0;
	end
	
	return velocity
end

print("Hello from Player.lua")