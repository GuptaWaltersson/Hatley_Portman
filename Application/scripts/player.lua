local player {}

player.components = {
	position = {x = 0, y = 0},
	sprite = {texture = "../Textures/Portman_v1.png"}
}

player.behaviour = {
	OnCreate = function(self)
		print("Player is Spawned, ID", self.ID)
	end
	
	OnUpdate = function(self)
		self.position.x = self.position.x + 100 * delta
	end
}

return player