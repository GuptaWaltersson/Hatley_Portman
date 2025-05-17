local block={}

function block.OnCreate(self)

	
end

function block.OnUpdate()
	
end

function block.Ground()

	for i = 0, 22 do
		local entity = scene.CreateEntity()
		scene.SetComponent(entity, "tag", "ground1")
		scene.SetComponent(entity, "sprite", "../Textures/tile_0022.png")
		scene.SetComponent(entity, "boundingbox", { width = 72, height = 72})
		scene.SetComponent(entity, "position", { x = 18+(72*i), y =  836})
	end

	for i = 0, 22 do
		local entity = scene.CreateEntity()
		scene.SetComponent(entity, "tag", "ground2")
		scene.SetComponent(entity, "sprite", "../Textures/tile_0122.png")
		scene.SetComponent(entity, "boundingbox", { width = 72, height = 72})
		scene.SetComponent(entity, "position", { x = 18+(72*i), y = 908})
	end
end

cloudCounter = 0
function block.createCloud(length,posX,posY)
	print("call print cloud")
	for i=0, length do
		local entity = scene.CreateEntity()
		scene.SetComponent(entity,"tag","cloud")
		scene.SetComponent(entity, "id", cloudCounter)

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
	cloudCounter = cloudCounter + 1
end



local function createSmallBlock(posX,posY)
	local entity = scene.CreateEntity()
	scene.SetComponent(entity,"tag","smallblock")
	scene.SetComponent(entity,"sprite","../Textures/tile_0146.png")
	scene.SetComponent(entity,"boundingbox",{width = 60, height = 30})
	scene.SetComponent(entity,"position",{x=posX,y=posY})
end



mushroomCounter = 0
function block.createMushroom(length,posX,posY)
	local mushroomBlock = {width = length, height = 1, speed = 0, duration = 0, waitTime = 0}
	for i = 0, length do
		local entity = scene.CreateEntity()
		scene.SetComponent(entity,"tag","mushroom")
		scene.SetComponent(entity, "id", mushroomCounter)
		scene.SetComponent(entity,"block",mushroomBlock)
		if i == 0 then
			scene.SetComponent(entity,"sprite","../Textures/tile_0014.png")
			scene.SetComponent(entity,"boundingbox",{width=60,height=30})
		elseif i == length/2 then
			scene.SetComponent(entity,"sprite","../Textures/tile_0012.png")
			scene.SetComponent(entity,"boundingbox",{width=72,height=30})
		elseif i == length then
			scene.SetComponent(entity,"sprite","../Textures/tile_0015.png")
			scene.SetComponent(entity,"boundingbox",{width=60,height=30})
		else
			scene.SetComponent(entity,"sprite","../Textures/tile_0013.png")
			scene.SetComponent(entity,"boundingbox",{width=72,height=30})
		end

		scene.SetComponent(entity,"position",{x=posX+72*i,y=posY})
	end

	for i = 1, (836-posY)/72 do
		local entity = scene.CreateEntity()
		scene.SetComponent(entity,"tag","mushroom")
		scene.SetComponent(entity, "id", mushroomCounter)
		scene.SetComponent(entity,"block",mushroomBlock)
		scene.SetComponent(entity,"sprite","../Textures/tile_0032.png")
		scene.SetComponent(entity,"position",{x = posX +(72*length/2),y=posY+68*i})
	end
	mushroomCounter = mushroomCounter + 1
end


function slimTree(Height,posX,posY,treeBlock)
	for i = 1, Height do
		local entity = scene.CreateEntity()
		scene.SetComponent(entity,"tag","tree")
		scene.SetComponent(entity,"id",treeCounter)
		scene.SetComponent(entity,"block",treeBlock)
		if i == 1 then
			scene.SetComponent(entity,"sprite","../Textures/leafs/tile_0036.png")
		elseif i == Height then
			scene.SetComponent(entity,"sprite","../Textures/leafs/tile_0076.png")
		else
			scene.SetComponent(entity,"sprite","../Textures/leafs/tile_0056.png")
		end
		scene.SetComponent(entity,"position",{x=posX,y=posY+72*i-72})
		scene.SetComponent(entity,"boundingbox",{width = 60,height = 60})
	end
end

function chunkyTree(Width,posX,posY,treeBlock)
	for i = 1, Width do
		local entity = scene.CreateEntity()
		scene.SetComponent(entity,"tag","tree")
		scene.SetComponent(entity,"id",treeCounter)
		scene.SetComponent(entity,"block",treeBlock)

		if i == 1 then
			scene.SetComponent(entity,"sprite","../Textures/leafs/tile_0077.png")
		elseif i == Width then
			scene.SetComponent(entity,"sprite","../Textures/leafs/tile_0079.png")
		else
			scene.SetComponent(entity,"sprite","../Textures/leafs/tile_0078.png")
		end
		
		scene.SetComponent(entity,"position",{x=posX+72*i-72,y=posY})
		scene.SetComponent(entity,"boundingbox",{width=60,height=60})
	end
end

function Tree (Height,Width,posX,posY,treeBlock) -- Call this when width and height are at least 2 each
	for i =1, Height do
		for j= 1, Width do
			local entity = scene.CreateEntity()
			scene.SetComponent(entity,"tag","tree")
			scene.SetComponent(entity,"id",treeCounter)
			scene.SetComponent(entity,"block",treeBlock)

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
			scene.SetComponent(entity,"position",{x=posX+72*j-72,y=posY+72*i-72})
			scene.SetComponent(entity,"boundingbox",{width=60,height=60})
		end
	end		
end

function createTrunk(Width,Height,posX,posY,treeBlock)
	treeMid = posX + Width*36-36;
	treeBot = posY + Height *72-12;

	for i=0, (836-treeBot)/72 do
		local entity = scene.CreateEntity()
		scene.SetComponent(entity,"tag","tree")
		scene.SetComponent(entity,"id",treeCounter)
		scene.SetComponent(entity,"block",treeBlock)

		if i == 0 then
			scene.SetComponent(entity,"sprite","../Textures/tile_0096.png")
		else
			scene.SetComponent(entity,"sprite","../Textures/tile_0116.png")
		end
		scene.SetComponent(entity,"position",{x=treeMid,y=treeBot+i*72})
	end
			
end

treeCounter = 0
function block.createTree(Width,Height,posX,posY)
	treeBlock = {width = Width, height = Height, speed = 0, duration=0, waitTime = 0}
	if Height == 1 and Width == 1 then
		local entity = scene.CreateEntity()
		scene.SetComponent(entity,"block",treeBlock)
		scene.SetComponent(entity,"tag","tree")
		scene.SetComponent(entity,"id",treeCounter)
		scene.SetComponent(entity,"sprite","../Textures/leafs/tile_0016.png")
		scene.SetComponent(entity,"position",{x=posX,y=posY})
		scene.SetComponent(entity,"boundingbox",{width=60,height=60})
	elseif Width == 1 then
		slimTree(Height,posX,posY,treeBlock)
	elseif Height == 1 then
		chunkyTree(Width,posX,posY,treeBlock)
	else
		Tree(Height,Width,posX,posY,treeBlock)
	end
	createTrunk(Width,Height,posX,posY,treeBlock)
	treeCounter = treeCounter + 1
end

function block.createPlayer(posX, posY)
	local entity = scene.CreateEntity()
	scene.SetComponent(entity, "sprite", "../Textures/Portman.png")
	scene.SetComponent(entity, "position", position)
	scene.SetComponent(entity, "boundingbox", { width = 64, height = 64})
	scene.SetComponent(entity, "movement",movement)
	scene.SetComponent(entity, "gravity", 1800)
	scene.SetComponent(entity, "playertag",true)
	scene.SetComponent(entity, "tag", "player")
	scene.SetComponent(entity, "lastmove","left")
	print("player created")
end

return block