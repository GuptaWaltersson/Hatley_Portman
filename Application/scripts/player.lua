local player = {}

-- Compontents
local entity = scene.CreateEntity()

scene.SetComponent(entity, "sprite", "../Textures/Portman_v1.png")
scene.SetComponent(entity, "boundingbox", { width = 64, height = 64})
scene.SetComponent(entity, "position", { x = 200, y = 200})

velocity = {dx=0.1,dy=0.1}
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