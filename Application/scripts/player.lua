
local player = {}

position = {x=200,y=700}
movement = {dx=0.0,dy=-300.0,ax = 2400, ay=700}

-- Behaviours
function player.OnCreate(self)
	scene.SetComponent(self.ID, "sprite", "../Textures/Portman.png")
	scene.SetComponent(self.ID, "position", position)
	scene.SetComponent(self.ID, "boundingbox", { width = 64, height = 64})
	scene.SetComponent(self.ID, "movement",movement)
	scene.SetComponent(self.ID, "gravity", 1800)
	scene.SetComponent(self.ID, "playertag",true)
	scene.SetComponent(self.ID, "tag", "player")
	scene.SetComponent(self.ID, "lastmove","left")
	print("player created")
end

function player.OnUpdate(delta)
	
	--print("Player Update!")
	--position = { x = 0, y = 0}
	--scene.SetComponent(player.ID, "position", position)
end

return player
