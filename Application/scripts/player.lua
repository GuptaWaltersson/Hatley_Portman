local player = {}

-- Compontents
local entity = scene.CreateEntity()

scene.SetComponent(entity, "sprite", "../Textures/Portman_v1.png")
scene.SetComponent(entity, "boundingbox", { width = 64, height = 64})

position = {x=0,y=0}
velocity = {dx=0.3,dy=0.3}
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