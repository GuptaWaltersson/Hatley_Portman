local coin = {}

function coin.OnCreate(self)
	print("Lua Coin created!")
end

function coin.OnUpdate(self, delta)
	-- Update logic for the coin can be added here if needed
end

function coin.OnCollision(self, other)
	print("Lua Coin collected!")
	coinCounter = coinCounter + 1
	coinNumber.SetNumber(text1, coinCounter)
	scene.RemoveEntity(self.ID)
end

return coin
