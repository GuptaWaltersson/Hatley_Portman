local cloud={}
cloud.co = nil


function cloud.OnCreate(self,delta)
	local cloudID = 0

	cloud.co = coroutine.create(function()
		while true do
			moveCloud(cloudID,50,2,delta)
			wait (1, delta)
			moveCloud(cloudID,-50,2,delta)
			wait(1,delta)
			
		end
	end)
end

function cloud.OnUpdate(self,delta)
	if cloud.co and coroutine.status(cloud.co) ~= "dead" then
		local ok, err = coroutine.resume(cloud.co,delta)
		if not ok then print( "Cloud Coroutine Error: ",err) end
	end
end



clouds = {} -- Global table for all clouds
local cloudCounter = 0
function createCloud(length,posX,posY)
	
	clouds[cloudCounter] = {}

	for i=0, length do
		local entity = scene.CreateEntity()
		table.insert(clouds[cloudCounter],entity)
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

function moveCloud (cloudID,dx,duration,delta)
	cloud = clouds[cloudID]
	if not cloud then return end

	local elapsed =0
	while elapsed < 4
		for _,entity in ipairs(cloud) do
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


return cloud