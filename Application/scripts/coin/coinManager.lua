coinManager = {}
local coinCounter = 0

function coinManager.CreateSceneManager()
	local entity = scene.CreateEntity()
	scene.SetComponent(self.ID, "tag", "coinManager")
end

function coinManager.CreateEditManager()
	local entity = scene.CreateEntity()
	scene.SetComponent(entity, "tag", "coinManager")
end

function coinManager.CreateCoin(posX, posY)
	local entity = scene.CreateEntity()
	scene.SetComponent(entity, "tag", "coin")
	scene.SetComponent(entity, "sprite", "../Textures/tile_0067.png")
	scene.SetComponent(entity, "behaviour", "scripts/coin/coin.lua")
	scene.SetComponent(entity, "position", { x = posX, y = posY})
	scene.SetComponent(entity, "boundingbox", { width = 50, height = 50})
	scene.SetComponent(entity, "id", coinCounter)
	coinCounter = coinCounter + 1
end

return coinManager



