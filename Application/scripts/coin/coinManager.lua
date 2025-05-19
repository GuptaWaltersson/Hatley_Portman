
nrOfCoins = 5
cCounter = 0

local coinCounterEntity = scene.CreateEntity()
scene.SetComponent(coinCounterEntity, "behaviour", "scripts/coin/coinCounter.lua")

local TextEntity = scene.CreateEntity()
scene.SetComponent(TextEntity, "sprite", "../Textures/Numbers/tile_0170.png")
scene.SetComponent(TextEntity, "position", {x=1460, y=30})

local coinNumberEntity = scene.CreateEntity()
scene.SetComponent(coinNumberEntity, "behaviour", "scripts/coin/coinNumber.lua")

