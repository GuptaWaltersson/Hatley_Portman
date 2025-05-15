local cloud={}

function cloud.OnCreate(self)

	
end

function cloud.OnUpdate()
	
end


local cloudCounter = 0
function createCloud(length,posX,posY)
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

function lerp(a,b,t)
	return a+ (b-a) *t
end


return cloud