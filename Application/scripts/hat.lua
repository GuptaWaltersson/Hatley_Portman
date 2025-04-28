local hat = {}



position = {x=1000,y=500}
movement = {dx=0.0,dy=0.0,ax = 2400, ay=700}


-- Behaviours
function hat.OnCreate(self)
	print("Hat created!")
	scene.SetComponent(self.ID,"sprite","../Textures/Portman_hat.png")
	scene.SetComponent(self.ID,"hattag",1)
	scene.SetComponent(self.ID,"position",position)
	scene.SetComponent(self.ID, "boundingbox", { width = 64, height = 32})
	scene.SetComponent(self.ID,"movement",movement)
end

function hat.OnUpdate(delta)
	--print("Hat updated (:")
end

function hat.throw(delta)
	print("hat kast")
	position = {x=800,y=500}
	scene.SetComponent(hat.ID,"position",position)
end

return hat