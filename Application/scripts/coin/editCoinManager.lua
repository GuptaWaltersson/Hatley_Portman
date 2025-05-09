local coinManager = {}

function coinManager.OnCreate(self)

end

function coinManager.OnUpdate(self,delta)

end

function coinManager.CreateCoin(posX,posY)
    local coin = scene.CreateEntity()
    scene.SetComponent(coin,"position",{x=posX,y=posY})
    scene.SetComponent(coin,"behaviour","scripts/coin/coin.lua")
end




return coinManager