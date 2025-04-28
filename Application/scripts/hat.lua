local hat = {}

HatType = 
{
	DEFAULT = 1,
	MAGIC = 2,
	LEGENDARY = 3

}

position = {x=1000,y=500}
movement = {dx=0.0,dy=0.0,ax = 2400, ay=700}
local hat_tag = 1

-- Behaviours
function hat.OnCreate(self)
	print("Hat created!")
	scene.SetComponent(self.ID,"sprite","../Textures/Portman_hat.png")
	scene.SetComponent(self.ID,"hattag",hat_tag)
	scene.SetComponent(self.ID,"position",position)
	scene.SetComponent(self.ID, "boundingbox", { width = 64, height = 32})
	scene.SetComponent(self.ID,"movement",movement)
end

function hat.OnUpdate(delta)
	position.x = position.x + movement.dx
	print(movement.dx)
	scene.SetComponent(hat.ID,"position",position)
	scene.SetComponent(hat.ID,"movement",movement)

end

function hat.throw(delta)
	print("hat kast")
	scene.GetComponent(hat.ID,"hattag",hat_tag)
	
    if hat_tag == HatType.DEFAULT then
        print("Default Hat Behavior")
		
    elseif hat_tag == HatType.MAGIC then
        print("Magic Hat Behavior")
    elseif hat_tag == HatType.LEGENDARY then
        print("Legendary Hat Behavior")
    else
        print("Unknown hat type:"..hat_tag)
    end

end

local function defaultThrow()
	xSpeed = 50
	movement.dx = xSpeed
	scene.SetComponent(hat.ID,"movement",movement)
end

return hat