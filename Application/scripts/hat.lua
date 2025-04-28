local hat = {}

-- Compontents
local entity = scene.CreateEntity()

scene.SetComponent(entity, "sprite", "../Textures/Portman_hat.png")
hat.position = {x = 0, y = 0}

position = {x=1000,y=500}
movement = {dx=0.0,dy=0.0,ax = 2400, ay=700}

scene.SetComponent(entity,"position",position)
scene.SetComponent(entity, "boundingbox", { width = 64, height = 32})
scene.SetComponent(entity,"movement",movement)
--scene.SetComponent(entity,"gravity",1800)


-- Behaviours
function hat.OnCreate(self)
	print("Hat created!")
	scene.SetComponent(self.ID, "position", {x = 400, y = 500})
end

function hat.OnUpdate(delta)
	local dx, dy = 0, 0

	local pos = scene.GetComponent(self.ID, "position")
	pos.x = pos.x + dx
	pos.y = pos.y + dy

	scene.SetComponent(self.ID, "position", pos)
end

return hat