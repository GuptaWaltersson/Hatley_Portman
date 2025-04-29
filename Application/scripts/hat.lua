local hat = {}
local instance ={
	ID = nil
}
HatType = 
{
	DEFAULT = 1,
	MAGIC = 2,
	LEGENDARY = 3

}

position = {x=1000,y=700}
movement = {dx=0.0,dy=0.0,ax = 2400, ay=700}
local hat_tag = 1
local currentThrow = nil


-- Behaviours
function hat.OnCreate(self)
		print("Hat created!")
	print("Self:", self)
	print("Self.ID:", self and self.ID)

	instance.ID = self and self.ID
	

	if self.ID == nil then
		print("nil at start")
	end

	

	scene.SetComponent(instance.ID,"sprite","../Textures/Portman_hat.png")
	scene.SetComponent(instance.ID,"hattag",hat_tag)
	scene.SetComponent(instance.ID,"position",position)
	--scene.SetComponent(instance.ID, "boundingbox", { width = 64, height = 32})
	scene.SetComponent(instance.ID,"movement",movement)
	
end

function hat.OnUpdate(self,delta)
	
	if self.ID == nil then
		print( "no id in onUpdate")
	end

	if currentThrow then
		currentThrow(self,delta)
	end
end

function hat.throw(delta)
	print("hat kast")
	
    if hat_tag == HatType.DEFAULT then
        print("Default Hat Behavior")
		currentThrow = defaultThrow
    elseif hat_tag == HatType.MAGIC then
        print("Magic Hat Behavior")
    elseif hat_tag == HatType.LEGENDARY then
        print("Legendary Hat Behavior")
    else
        print("Unknown hat type:"..hat_tag)
    end

end

function defaultThrow(self,delta)


	movement.dx = -100
	position = {x= position.x +movement.dx * delta, y= position.y}
	scene.SetComponent(self.ID,"position",position)
end

return hat