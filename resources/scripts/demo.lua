package.path = package.path .. ";C:/Dev/DV1570/resources/scripts/?.lua"

math.randomseed(os.time())

raylib = require 'Raylib'

function onUpdate()
	if raylib.IsKeyDown(Keys.KEY_W) then
		print("Key " .. Keys.KEY_W .." was pressed.")
	end
end