coinManager = {}
coinID = 0
coinCounter = 0
coinStarter = 0

coinNumber = require("scripts.coin.coinNumber")

function coinManager.CreateSceneManager()
	coinCounter = 0

	local entity = scene.CreateEntity()
	scene.SetComponent(entity, "tag", "coinManager")

	text1 = scene.CreateEntity()
	scene.SetComponent(text1, "tag", "text")
	scene.SetComponent(text1, "position", {x=1490, y=30})
	coinNumber.SetNumber(text1, coinCounter)

	local text2 = scene.CreateEntity()
	scene.SetComponent(text2, "tag", "text")
	scene.SetComponent(text2, "position", {x=1550, y=30})
	scene.SetComponent(text2, "sprite", "../Textures/Numbers/tile_0170.png")
	
	local text3 = scene.CreateEntity()
	scene.SetComponent(text3, "tag", "text")
	scene.SetComponent(text3, "position", {x=1610, y=30})
	coinNumber.SetNumber(text3, coinStarter)

end

function coinManager.CreateEditManager()
	coinStarter = 0
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
	scene.SetComponent(entity, "id", coinID)
	coinID = coinID + 1
	coinStarter = coinStarter + 1
end

function coinManager.LoadCoin(posX, posY)
	local entity = scene.CreateEntity()
	scene.SetComponent(entity, "tag", "coin")
	scene.SetComponent(entity, "sprite", "../Textures/tile_0067.png")
	scene.SetComponent(entity, "behaviour", "scripts/coin/coin.lua")
	scene.SetComponent(entity, "position", { x = posX, y = posY})
	scene.SetComponent(entity, "boundingbox", { width = 50, height = 50})
	scene.SetComponent(entity, "id", coinID)
	coinID = coinID + 1
end

return coinManager



