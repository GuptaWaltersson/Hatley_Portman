local player = {}

-- Compontents
local entity = scene.CreateEntity()

scene.SetComponent(entity, "sprite", "../Textures/Portman_v1.png")
--player.position = {x = 0, y = 0}

position = {x=400,y=400}
velocity = {dx=1.0,dy=1.0}
scene.SetComponent(entity,"position",position)
scene.SetComponent(entity,"velocity",velocity)
-- Behaviours
function player.OnCreate(self)
	print("Player created!")
	scene.SetComponent(self.ID, "position", {x = 400, y = 500})
end

function player.OnUpdate(delta)
	local dx, dy = 0, 0

	local pos = scene.GetComponent(self.ID, "position")
	pos.x = pos.x + dx
	pos.y = pos.y + dy

	scene.SetComponent(self.ID, "position", pos)
end

return player