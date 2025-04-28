

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
local last = 3
for i = 0, last do
    local entity = scene.CreateEntity()
  
    if i == 0 then
        scene.SetComponent(entity, "sprite", "../Textures/tile_0153.png")
    elseif i == last then
        scene.SetComponent(entity, "sprite", "../Textures/tile_0155.png")
	else
        scene.SetComponent(entity, "sprite", "../Textures/tile_0154.png")
    end

    scene.SetComponent(entity, "boundingbox", { width = 60, height = 30 })
    scene.SetComponent(entity, "position", { x = 300 + (60 * i), y = 550 })
end

for i = 0, 1 do
	local entity = scene.CreateEntity()
	scene.SetComponent(entity, "sprite", "../Textures/tile_0156.png")
	scene.SetComponent(entity, "boundingbox", { width = 60, height = 30 })
	scene.SetComponent(entity, "position", { x = 700 + (300 * i), y = 650 })
end


--Behaviors
function block.OnCreate(self)
	print("Block spawned")
end

function block.OnUpdate(delta)
	print("Block updated")
end
