local block = {}

--Components
local entity = scene.CreateEntity()

scene.SetComponent(entity, "sprite", "../Textures/tile_0000.png")
scene.SetComponent(entity, "boundingbox", { x = 64, y = 64})
scene.SetComponent(entity, "position", { x = 500, y = 500})

--Behaviors
function block.OnCreate(self)
	print("Block spawned")
end

function block.OnUpdate(delta)
	print("Block updated")
end

return block