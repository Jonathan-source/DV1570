package.path = package.path .. ";/?.lua" 

require 'Keys'

local Raylib = {

	IsKeyDown = function(key)
		return _IsKeyDown(key)
	end,

}

return Raylib