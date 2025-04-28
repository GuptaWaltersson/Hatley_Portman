local player = {}

-- Behaviours
function player.OnCreate(self)
	print("Player created!")
	scene.SetComponent(self.ID, "position", {x = 400, y = 200})
end

function player.OnUpdate(delta)
	print("Player Update!")
end

return player