
--Components
for i = 0, 22 do
	local entity = scene.CreateEntity()
	scene.SetComponent(entity, "tag", "block")
	scene.SetComponent(entity, "sprite", "../Textures/tile_0022.png")
	scene.SetComponent(entity, "boundingbox", { width = 72, height = 72})
	scene.SetComponent(entity, "position", { x = 18+(72*i), y =  836})
end

for i = 0, 22 do
	local entity = scene.CreateEntity()
	scene.SetComponent(entity, "tag", "block")
	scene.SetComponent(entity, "sprite", "../Textures/tile_0122.png")
	scene.SetComponent(entity, "boundingbox", { width = 72, height = 72})
	scene.SetComponent(entity, "position", { x = 18+(72*i), y = 908})
end

local cloudLength = 5
for i = 0, cloudLength do
    local entity = scene.CreateEntity()
	scene.SetComponent(entity, "tag", "block")
  
    if i == 0 then
        scene.SetComponent(entity, "sprite", "../Textures/tile_0153.png")
    elseif i == cloudLength then
        scene.SetComponent(entity, "sprite", "../Textures/tile_0155.png")
	else
        scene.SetComponent(entity, "sprite", "../Textures/tile_0154.png")
    end

    scene.SetComponent(entity, "boundingbox", { width = 60, height = 30 })
    scene.SetComponent(entity, "position", { x = 300 + (60 * i), y = 550 })
end

for i = 0, 1 do
	local entity = scene.CreateEntity()
	scene.SetComponent(entity, "tag", "block")
	scene.SetComponent(entity, "sprite", "../Textures/tile_0156.png")
	scene.SetComponent(entity, "boundingbox", { width = 60, height = 30 })
	scene.SetComponent(entity, "position", { x = 770 + (300 * i), y = 700 })
end

local mushroomLength = 6
local mushroomHeight = 4

for i = 0, mushroomLength do
    local entity = scene.CreateEntity()
	scene.SetComponent(entity, "tag", "block")
  
    if i == 0 then
        scene.SetComponent(entity, "sprite", "../Textures/tile_0014.png")
    elseif i == mushroomLength then
        scene.SetComponent(entity, "sprite", "../Textures/tile_0015.png")
	elseif i==mushroomLength/2 then
		scene.SetComponent(entity, "sprite", "../Textures/tile_0012.png")
	else
        scene.SetComponent(entity, "sprite", "../Textures/tile_0013.png")
    end

    scene.SetComponent(entity, "boundingbox", { width = 60, height = 30 })
    scene.SetComponent(entity, "position", { x = 1000 + (60 * i), y = 772-(mushroomHeight+1)*72 })
end


for i = 0, mushroomHeight do
	local entity = scene.CreateEntity()
	scene.SetComponent(entity, "tag", "block")
	scene.SetComponent(entity, "sprite", "../Textures/tile_0032.png")
	scene.SetComponent(entity, "position", { x = 1000 + (60 * mushroomLength/2), y = 770 - 72 *i })
end
