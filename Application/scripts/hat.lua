local hat = {}

HatType = 
{
	ONHEAD =0,
	DEFAULT = 1,
	MAGIC = 2,
	LEGENDARY = 3
}

--Start values
local position = {x=-50,y=-50}
local movement = {dx=0.0,dy=0.0,ax = 2400, ay=700}
local hat_tag = 0
local hat_behaviour = 0
local currentThrow = nil
local lastmove =""

-- Behaviours
function hat.OnCreate(self)
	scene.SetComponent(self.ID,"sprite","../Textures/Hat.png")
	scene.SetComponent(self.ID,"hattag",{onHead = true, hatType = 1})
	scene.SetComponent(self.ID, "tag", "hat")
	scene.SetComponent(self.ID,"position",position)
	scene.SetComponent(self.ID,"movement",movement)
	scene.SetComponent(self.ID,"lastmove","left")
	scene.SetComponent(self.ID,"boundingbox",{width = 60,height = 30})
	
end

function hat.OnUpdate(self,delta)
	
	position.x,position.y = scene.GetComponent(self.ID, "position")

	if currentThrow then
		currentThrow(self,delta,lastmove)
	end
end

function hat.throw(self,delta)

	onHead,hat_tag = scene.GetComponent(self.ID,"hattag")
	local mov = {dx = 0,dy = 0, ax=0, ay=0}
	lastmove = scene.GetComponent(self.ID,"lastmove",lastmove)
    if hat_tag == HatType.DEFAULT then

		if lastmove == "left" then
			mov.dx = -1000
		else
			mov.dx = 1000
		end
		scene.SetComponent(self.ID,"movement",mov)
		currentThrow = defaultThrow
		currentThrow(self,delta,lastmove)
    elseif hat_tag == HatType.MAGIC then

		
		if lastmove == "left" then
			mov.dx = -600
		else
			mov.dx = 600
		end
		mov.dy = -600
		scene.SetComponent(self.ID,"movement",mov)
		currentThrow = magicThrow
    elseif hat_tag == HatType.LEGENDARY then
		if lastmove == "left" then
			mov.dx = -100
		else
			mov.dx = 100
		end
		mov.dy = -900
		scene.SetComponent(self.ID,"movement",mov)
		currentThrow = magicThrow
    else
        --print("Unknown hat type:"..hat_tag..", no throw")
    end
end

function hat.newThrow(self,throw)
	print("New hat throw: "..throw)
	scene.SetComponent(self.ID,"hattag",{onHead = true, hatType = throw})
end

function defaultThrow(self,delta,lastmove)
	local mov = scene.GetComponent(self.ID,"movement")
	local posX,posY = scene.GetComponent(self.ID,"position")

	position = {x= posX + mov.dx*delta, y=posY}
	scene.SetComponent(self.ID,"position",position)
end

function magicThrow(self, delta)
	
	local mov = scene.GetComponent(self.ID,"movement")
	local posX,posY = scene.GetComponent(self.ID,"position")
	local gravity = 980  -- pixels per second squared

 
    -- Apply gravity to vertical velocity
    mov.dy = mov.dy + gravity * delta

    -- Apply movement
    posX = posX + mov.dx * delta
    posY = posY + mov.dy * delta

    -- Set updated components back
	pos = {x=posX,y=posY}
    scene.SetComponent(self.ID, "position", pos)
    scene.SetComponent(self.ID, "movement", mov)
end

return hat