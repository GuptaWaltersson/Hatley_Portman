
-- Compontents
local entity = scene.CreateEntity()

scene.SetComponent(entity, "sprite", "../Textures/Portman_v1.png")

position = {x=0,y=0}
movement = {dx=0.0,dy=-300.0,ax = 2400, ay=700}

scene.SetComponent(entity,"position",position)
scene.SetComponent(entity, "boundingbox", { width = 64, height = 64})

scene.SetComponent(entity,"movement",movement)
scene.SetComponent(entity,"gravity",1800)
scene.SetComponent(entity,"playertag",true)
scene.SetComponent(entity,"behaviour", "scripts/playerB.lua")


