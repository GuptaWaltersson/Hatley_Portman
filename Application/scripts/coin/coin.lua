local coin = {}
coin.cor = {}
coinCounter = 0
framedelta = 0
function coin.OnCreate(self)
	print("Lua Coin created!")
	local entity = self.ID
	--local x, y = scene.GetComponent(entity,"position")

	coin.cor[entity] = coroutine.create(function()
		local time = 0

		while true do
			time = time + coroutine.yield()
			local offset = math.sin(time*2) * 0.05 
			local x,y = scene.GetComponent(entity,"position")
			scene.SetComponent(entity,"position",{x = x,y= y + offset})
			--print("set position:"..posX..posY+offset.." babooom")
		end


	end)
end

function coin.OnUpdate(self, delta)
	local id = self.ID
	local co = coin.cor[id]
	if co and coroutine.status(co) ~="dead" then
		local ok, err = coroutine.resume(co,delta)
		if not ok then
			print("error in coin coroutine: coin "..id)
		end
	end

end

function coin.OnCollision(self, other)
	print("Lua Coin collected!")
	
	scene.RemoveEntity(self.ID)
end



return coin
