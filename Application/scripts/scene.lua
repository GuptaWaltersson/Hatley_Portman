
-- Compontents
local playerEntity = scene.CreateEntity()
scene.SetComponent(playerEntity, "behaviour", "scripts/player.lua")



local coin1 = scene.CreateEntity()
scene.SetComponent(coin1, "position", {x=400, y=450})
scene.SetComponent(coin1, "behaviour", "scripts/coin.lua")

local coin2 = scene.CreateEntity()
scene.SetComponent(coin2, "position", {x=1200, y=700})
scene.SetComponent(coin2, "behaviour", "scripts/coin.lua")

local coin3 = scene.CreateEntity()
scene.SetComponent(coin3, "position", {x=600, y=600})
scene.SetComponent(coin3, "behaviour", "scripts/coin.lua")
