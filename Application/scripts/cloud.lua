local cloud={}
cloud.cor = {} 
clouds = {} -- Global table for all clouds
local cloudCounter = 0
local cloudID = 0

function moveCloud (cloudID,dx,duration,delta)
	cloudGroup = clouds[cloudID]
	if not cloudGroup then return end

	local elapsed =0
	while elapsed < duration do
		for _,entity in ipairs(cloudGroup) do
			local posX,posY = scene.GetComponent(entity,"position")
			posX = posX + dx* delta
			scene.SetComponent(entity,"position",{x=posX,y=posY})
		end
		coroutine.yield(0)
		elapsed = elapsed + delta
	end
end

function wait(time,delta)
	local timer = 0
	while timer < time do
		coroutine.yield()
		timer = timer + delta
	end
end

function lerp(a,b,t)
	return a+ (b-a) *t
end


function cloud.OnCreate(self,delta)
	--cloud.NewCloud(3,300,300,50,2)
end

function cloud.OnUpdate(self, delta)
	for id, co in pairs(cloud.cor) do
		
		if coroutine.status(co) ~= "dead" then
			local ok, err = coroutine.resume(co,delta)
			if not ok then print("Cloud Coroutine Error [cloudID " .. id .. "]:", err) end
		end
		
	end

end




function cloud.NewCloud(length,posX,posY,speed,duration)
	local id = cloudCounter	

	clouds[id] = {}

	for i=0, length do
		local entity = scene.CreateEntity()
		table.insert(clouds[id],entity)
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
	print("new cloud called")
	cloud.cor[id] = coroutine.create(function(delta)
		while true do 
			
			moveCloud(id, speed, duration, delta)
			wait(1, delta)

			
			moveCloud(id, -speed, duration, delta)

			delta = coroutine.yield()
			wait(1, delta)
		end
	end)
	print("Coroutine stored for cloud ID:", id)
	cloudCounter = cloudCounter + 1

end


return cloud