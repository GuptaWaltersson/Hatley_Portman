
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


function slimTree(Height,posX,posY)
	for i = 1, Height do
		local entity = scene.CreateEntity()
		scene.SetComponent(entity,"tag","block")
		if i == 1 then
			scene.SetComponent(entity,"sprite","../Textures/leafs/tile_0036.png")
		elseif i == Height then
			scene.SetComponent(entity,"sprite","../Textures/leafs/tile_0076.png")
		else
			scene.SetComponent(entity,"sprite","../Textures/leafs/tile_0056.png")
		end
		scene.SetComponent(entity,"position",{x=posX,y=posY+72*i})
		scene.SetComponent(entity,"boundingbox",{width = 60,height = 60})
	end
end

function chunkyTree(Width,posX,posY)
	for i = 1, Width do
		local entity = scene.CreateEntity()
		scene.SetComponent(entity,"tag","block")
		if i == 1 then
			scene.SetComponent(entity,"sprite","../Textures/leafs/tile_0077.png")
		elseif i == Width then
			scene.SetComponent(entity,"sprite","../Textures/leafs/tile_0079.png")
		else
			scene.SetComponent(entity,"sprite","../Textures/leafs/tile_0078.png")
		end
		
		scene.SetComponent(entity,"position",{x=posX+72*i,y=posY})
		scene.SetComponent(entity,"boundingbox",{width=60,height=60})
	end
end

function Tree (Height,Width,posX,posY) -- Call this when width and height are at least 2 each
	for i =1, Height do
		for j= 1, Width do
			local entity = scene.CreateEntity()
			scene.SetComponent(entity,"tag","block")
			if j == 1 and i == 1 then
				scene.SetComponent(entity,"sprite","../Textures/leafs/tile_0017.png")
			elseif j == Width and i == 1 then
				scene.SetComponent(entity,"sprite","../Textures/leafs/tile_0019.png")
			elseif i == 1 then
				scene.SetComponent(entity,"sprite","../Textures/leafs/tile_0018.png")
			elseif j == 1 and i == Height then
				scene.SetComponent(entity,"sprite","../Textures/leafs/tile_0057.png")
			elseif j == (Width+1)/2 and i == Height then 
				scene.SetComponent(entity,"sprite","../Textures/leafs/tile_0097.png")
			elseif j== Width and i == Height then
				scene.SetComponent(entity,"sprite","../Textures/leafs/tile_0059.png")
			elseif j==1 then 
				scene.SetComponent(entity,"sprite","../Textures/leafs/tile_0037.png")
			elseif j==Width then
				scene.SetComponent(entity,"sprite","../Textures/leafs/tile_0039.png")
			elseif i== Height then
				scene.SetComponent(entity,"sprite","../Textures/leafs/tile_0058.png")
			else
				scene.SetComponent(entity,"sprite","../Textures/leafs/tile_0038.png")
			end
			scene.SetComponent(entity,"position",{x=posX+72*j,y=posY+72*i})
			scene.SetComponent(entity,"boundingbox",{width=60,height=60})
		end
	end		
end


function createTree(Height,Width,posX,posY)
	if Height == 1 and Width == 1 then
		local entity = scene.CreateEntity()
		scene.SetComponent(entity,"tag","block")
		scene.SetComponent(entity,"sprite","../Textures/leafs/tile_0016.png")
		scene.SetComponent(entity,"position",{x=posX,y=posY})
		scene.SetComponent(entity,"boundingbox",{width=60,height=60})
	elseif Width == 1 then
		slimTree(Height,posX,posY)
	elseif Height == 1 then
		chunkyTree(Width,posX,posY)
	else
		Tree(Height,Width,posX,posY)
	end
end

--createMushroom(6,6,1000,400) --Length, Height, X position, Y position
--createCloud(5,300,550) --Length of cloud, X position, Y position
--createCloud(8,500,170)
--createSmallBlock(770,750) -- X postion, Y position
--createSmallBlock(1070,750)
createTree(3,3,500,500)
createTree(1,1,200,200)