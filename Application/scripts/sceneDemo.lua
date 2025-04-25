local health = 100

for _ = 1, 100 do
	local entity = scene.CreateEntity()
	local tickDamage = math.random(1, 10)
	scene.SetComponent(entity, "health", health)
	scene.SetComponent(entity, "poison", tickDamage)
end


local Gentity = scene.CreateEntity()
scene.SetComponent(Gentity,"gravity")
scene.SetComponent(entity, "behaviour", "monster.lua")

local player = scene.CreateEntity()
position = {x=800,y=450}
scene.SetComponent(player,"position",position)
velocity = {dx = 10.0, dy=10.0}
scene.SetComponent(player,"velocity",velocity)
