

--Components
for i = 0, 22 do
	local entity = scene.CreateEntity()
	scene.SetComponent(entity, "sprite", "../Textures/tile_0022.png")
	scene.SetComponent(entity, "boundingbox", { width = 72, height = 72})
	scene.SetComponent(entity, "position", { x = 18+(72*i), y = 764})
end

for i = 0, 22 do
	local entity = scene.CreateEntity()
	scene.SetComponent(entity, "sprite", "../Textures/tile_0122.png")
	scene.SetComponent(entity, "boundingbox", { width = 72, height = 72})
	scene.SetComponent(entity, "position", { x = 18+(72*i), y = 836})
end

for i = 0, 22 do
	local entity = scene.CreateEntity()
	scene.SetComponent(entity, "sprite", "../Textures/tile_0122.png")
	scene.SetComponent(entity, "boundingbox", { width = 72, height = 72})
	scene.SetComponent(entity, "position", { x = 18+(72*i), y = 908})
end


--Behaviors
function block.OnCreate(self)
	print("Block spawned")
end

function block.OnUpdate(delta)
	print("Block updated")
end
