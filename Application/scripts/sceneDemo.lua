local health = 30

for _ = 1, 10 do
	local entity = scene.CreateEntity()
	local tickDamage = math.random(1, 10)
	scene.SetComponent(entity, "health", {value = health})
	scene.SetComponent(entity, "poison", {tickDamge = tickDamage})
end