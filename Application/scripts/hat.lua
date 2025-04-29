local hat = {}
local instance ={
	ID = nil
}
HatType = 
{
	ONHEAD =0,
	DEFAULT = 1,
	MAGIC = 2,
	LEGENDARY = 3

}
--Start values
position = {x=1000,y=700}
local movement = {dx=0.0,dy=0.0,ax = 2400, ay=700}
local hat_tag = 0
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
	hat_tag = scene.GetComponent(self.ID,"hattag",hat_tag)
	position = scene.GetComponent(self.ID, "position",position)
	--scene.SetComponent(self.ID,"hattag",hat_tag)
	hat.throw(delta)
	if currentThrow then
		currentThrow(self,delta)
	end
end

function hat.throw(delta)
	--print("hat kast")
	
	

    if hat_tag == HatType.DEFAULT then
        --print("Default Hat Behavior")
		currentThrow = defaultThrow
    elseif hat_tag == HatType.MAGIC then
        print("Magic Hat Behavior")

		currentThrow= magicThrow
    elseif hat_tag == HatType.LEGENDARY then
        print("Legendary Hat Behavior")
    else
        --print("Unknown hat type:"..hat_tag..", no throw")
    end

end

function defaultThrow(self,delta)


	movement.dx = -100
	position = {x= position.x + movement.dx*delta, y=position.y}
	scene.SetComponent(self.ID,"position",position)
end

function magicThrow(self, delta)
	self.movement.dx = -200
	self.movement.dy = -500
    -- Simulate gravity pulling downward
    local gravity = 980  -- pixels per second squared

    -- Apply gravity to vertical velocity
    self.movement.dy = self.movement.dy + gravity * delta

    -- Apply movement
    self.position.x = self.position.x + self.movement.dx * delta
    self.position.y = self.position.y + self.movement.dy * delta

    -- Update the position component in the scene
    scene.SetComponent(self.ID, "position", self.position)
end

return hat