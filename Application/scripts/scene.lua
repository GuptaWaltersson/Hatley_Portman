
-- Compontents
local playerEntity = scene.CreateEntity()
scene.SetComponent(playerEntity, "behaviour", "scripts/player.lua")



nrOfCoins = 3
cCounter = 0
local coinCounterEntity = scene.CreateEntity()
scene.SetComponent(coinCounterEntity, "behaviour", "scripts/coinCounter.lua")

local TextEntity = scene.CreateEntity()
scene.SetComponent(TextEntity, "sprite", "../Textures/Numbers/tile_0159.png")
scene.SetComponent(TextEntity, "position", {x=1460, y=30})

local coinNumberEntity = scene.CreateEntity()
scene.SetComponent(coinNumberEntity, "behaviour", "scripts/coinNumber.lua")

local coin1 = scene.CreateEntity()
scene.SetComponent(coin1, "position", {x=400, y=450})
scene.SetComponent(coin1, "behaviour", "scripts/coin.lua")

local coin2 = scene.CreateEntity()
scene.SetComponent(coin2, "position", {x=1200, y=700})
scene.SetComponent(coin2, "behaviour", "scripts/coin.lua")

local coin3 = scene.CreateEntity()
scene.SetComponent(coin3, "position", {x=600, y=600})
scene.SetComponent(coin3, "behaviour", "scripts/coin.lua")
