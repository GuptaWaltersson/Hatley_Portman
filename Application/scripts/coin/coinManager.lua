
nrOfCoins = 9
cCounter = 0

local coinPositions = {
    {x=300, y=700},
    {x=100, y=450},
    {x=300, y=250},
    {x=500, y=450},
    {x=700, y=250},
    {x=1300,y=300},
    {x=1000,y=100},
    {x=1500,y=700},
    {x=100, y=100}
}

for i = 1, nrOfCoins do
    local coin = scene.CreateEntity()
    scene.SetComponent(coin, "position", coinPositions[i])
    scene.SetComponent(coin, "behaviour", "scripts/coin/coin.lua")
end

local coinCounterEntity = scene.CreateEntity()
scene.SetComponent(coinCounterEntity, "behaviour", "scripts/coin/coinCounter.lua")

local TextEntity = scene.CreateEntity()
scene.SetComponent(TextEntity, "sprite", "../Textures/Numbers/tile_0170.png")
scene.SetComponent(TextEntity, "position", {x=1460, y=30})

local coinNumberEntity = scene.CreateEntity()
scene.SetComponent(coinNumberEntity, "behaviour", "scripts/coin/coinNumber.lua")

