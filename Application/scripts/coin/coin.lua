local coin = {}

function coin.OnCollision(self, other)
	print("Lua Coin collected!")
	
	scene.RemoveEntity(self.ID)
end

return coin
