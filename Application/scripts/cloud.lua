local cloud={}
cloud.cor = {} 
clouds = {} -- Global table for all clouds
local cloudCounter = 0
local cloudID = 0
local frameDelta = 0



function cloud.OnCreate(self,delta)
	--cloud.NewCloud(3,300,300,50,2)
end

function cloud.OnUpdate(self, delta)
	--print("onupdate")
	frameDelta = delta
	for id, co in pairs(cloud.cor) do
		
		if coroutine.status(co) ~= "dead" then
			local ok, err = coroutine.resume(co)
			if not ok then print("Cloud Coroutine Error [cloudID " .. id .. "]:", err) end
		end
		
	end

end




function cloud.NewCloud(self,length,posX,posY,speed,duration,waitTime)
	local id = cloudCounter	

	clouds[id] = {}
	local cloudStat = {length,1,speed,duration}
	for i=0, length do

		local entity = scene.CreateEntity()
		table.insert(clouds[id],entity)
		scene.SetComponent(entity,"tag","cloud")
		scene.SetComponent(entity, "id", cloudCounter)
		scene.SetComponent(entity,"block",cloudStat)

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
	cloud.cor[id] = coroutine.create(function()
		local direction = 1

		while true do 
			local elapsed = 0
			while elapsed < duration do
				for _,entity in ipairs(clouds[id]) do
					local posX, posY = scene.GetComponent(entity,"position")
					posX = posX + direction * speed * frameDelta
					scene.SetComponent(entity,"position",{x=posX,y=posY})
				end
				elapsed = elapsed + frameDelta
				coroutine.yield()
			end

			--wait
			local time = 0
			while time < waitTime do
				time = time + frameDelta
				coroutine.yield()
			end
			direction = -direction
		end
	end)
	print("Coroutine stored for cloud ID:", id)
	cloudCounter = cloudCounter + 1

end


return cloud