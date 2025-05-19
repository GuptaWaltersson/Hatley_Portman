local coin = {}
local coinCounter = require("scripts.coin.coinCounter")

-- Behaviours
function coin.OnCreate(self)
	scene.SetComponent(self.ID, "tag", "coin")
	scene.SetComponent(self.ID, "sprite", "../Textures/tile_0067.png")
	scene.SetComponent(self.ID, "boundingbox", { width = 50, height = 50})
	scene.SetComponent(self.ID, "id", self.ID)

	local x, y = scene.GetComponent(self.ID, "position")
    self.baseY = y
    self.time = 0
end

function coin.OnUpdate(self, delta)
	self.time = (self.time or 0) + delta

    local offsetY = math.sin(self.time * 2) * 7

    local x, y = scene.GetComponent(self.ID, "position")
    --scene.SetComponent(self.ID, "position", { x = x, y = self.baseY + offsetY})
end

function coinManager.CreateCoin(posX, posY)

end

function coin.OnCollision(self, other)
	print("Lua Coin collected!")
	cCounter = cCounter + 1
	
	scene.RemoveEntity(self.ID)
end

return coin
