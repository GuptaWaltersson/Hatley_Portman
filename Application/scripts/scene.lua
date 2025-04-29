-- Compontents

local hatEntity = scene.CreateEntity()
scene.SetComponent(hatEntity,"behaviour","scripts/hat.lua")

local playerEntity = scene.CreateEntity()
scene.SetComponent(playerEntity, "behaviour", "scripts/player.lua")



nrOfCoins = 4
cCounter = 0

local coinPositions = {
    {x=100, y=450},
    {x=300, y=450},
    {x=500, y=450},
    {x=700, y=550},
}

for i = 1, nrOfCoins do
    local coin = scene.CreateEntity()
    scene.SetComponent(coin, "position", coinPositions[i])
    scene.SetComponent(coin, "behaviour", "scripts/coin/coin.lua")
end

local coinCounterEntity = scene.CreateEntity()
scene.SetComponent(coinCounterEntity, "behaviour", "scripts/coin/coinCounter.lua")

local TextEntity = scene.CreateEntity()
scene.SetComponent(TextEntity, "sprite", "../Textures/Numbers/tile_0159.png")
scene.SetComponent(TextEntity, "position", {x=1460, y=30})

local coinNumberEntity = scene.CreateEntity()
scene.SetComponent(coinNumberEntity, "behaviour", "scripts/coin/coinNumber.lua")


