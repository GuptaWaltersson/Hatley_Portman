local block2 = {}

--Components
local entity = scene.CreateEntity()

scene.SetComponent(entity, "sprite", "../Textures/tile_0000.png")
scene.SetComponent(entity, "boundingbox", { x = 72, y = 72})
scene.SetComponent(entity, "position", { x = 344, y = 200})

--Behaviors
function block.OnCreate(self)
	print("Block spawned")
end

function block.OnUpdate(delta)
	print("Block updated")
end

return block