local player = {}

-- Compontents
local entity = scene.CreateEntity()

scene.SetComponent(entity, "sprite", "../Textures/Portman_v1.png")
player.position = {x = 0, y = 0}

position = {x=800,y=600}
velocity = {dx=0.0,dy=-300.0,ax = 2400, ay=800}

scene.SetComponent(entity,"position",position)
scene.SetComponent(entity, "boundingbox", { width = 64, height = 64})

scene.SetComponent(entity,"velocity",velocity)
scene.SetComponent(entity,"gravity",1800)
scene.SetComponent(entity,"playertag",true)
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