
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


local function createCloud(length,posX,posY)
	for i=0, length do
		local entity = scene.CreateEntity()
		scene.SetComponent(entity,"tag","block")
		if i == 0 then
			scene.SetComponent(entity,"sprite","../Textures/tile_0153.png")
		elseif i == length then
			scene.SetComponent(entity,"sprite","../Textures/tile_0155.png")
		else
			scene.SetComponent(entity,"sprite","../Textures/tile_0154.png")
		end

		scene.SetComponent(entity,"boundingbox",{width=60, height =30})
		scene.SetComponent(entity,"position",{x=posX +(72*i),y=posY})
	end
end



local function createSmallBlock(posX,posY)
	local entity = scene.CreateEntity()
	scene.SetComponent(entity,"tag","block")
	scene.SetComponent(entity,"sprite","../Textures/tile_0146.png")
	scene.SetComponent(entity,"boundingbox",{width = 60, height = 30})
	scene.SetComponent(entity,"position",{x=posX,y=posY})
end



local function createMushroom(length,height,posX,posY)
	for i = 0, length do
		local entity = scene.CreateEntity()
		scene.SetComponent(entity,"tag","block")
		
		if i == 0 then
			scene.SetComponent(entity,"sprite","../Textures/tile_0014.png")
		elseif i == length/2 then
			scene.SetComponent(entity,"sprite","../Textures/tile_0012.png")
		elseif i == length then
			scene.SetComponent(entity,"sprite","../Textures/tile_0015.png")
		else
			scene.SetComponent(entity,"sprite","../Textures/tile_0013.png")
		end

		scene.SetComponent(entity,"boundingbox",{width = 60, height = 30})
		scene.SetComponent(entity,"position",{x=posX+72*i,y=posY})
	end

	for i = 0, height do
		local entity = scene.CreateEntity()
		scene.SetComponent(entity,"tag","block")
		scene.SetComponent(entity,"sprite","../Textures/tile_0032.png")
		scene.SetComponent(entity,"position",{x = posX +(72*length/2),y=posY+72*i})
	end
end

createMushroom(6,6,1000,400) --Length, Height, X position, Y position
createCloud(5,300,550) --Length of cloud, X position, Y position
createCloud(8,500,170)
createSmallBlock(770,750) -- X postion, Y position
createSmallBlock(1070,750)