coinCounter = {}

-- Behaviours
function coinCounter.OnCreate(self)
	scene.SetComponent(self.ID, "tag", "counter")
	scene.SetComponent(self.ID, "position", {x=1390, y=30})
	scene.SetComponent(self.ID, "sprite", "../Textures/Numbers/0.png")
end

function coinCounter.OnUpdate(self,delta)


end

function coinCounter.newUpdate(self,cCounter)
	if cCounter == 1 then
		scene.SetComponent(self.ID, "sprite", "../Textures/Numbers/1.png")
	elseif cCounter == 2 then
		scene.SetComponent(self.ID, "sprite", "../Textures/Numbers/2.png")
	elseif cCounter == 3 then
		scene.SetComponent(self.ID, "sprite", "../Textures/Numbers/3.png")
	elseif cCounter == 4 then
		scene.SetComponent(self.ID, "sprite", "../Textures/Numbers/4.png")
	elseif cCounter == 5 then
		scene.SetComponent(self.ID, "sprite", "../Textures/Numbers/5.png")
	elseif cCounter == 6 then
		scene.SetComponent(self.ID, "sprite", "../Textures/Numbers/6.png")
	elseif cCounter == 7 then
		scene.SetComponent(self.ID, "sprite", "../Textures/Numbers/7.png")
	elseif cCounter == 8 then
		scene.SetComponent(self.ID, "sprite", "../Textures/Numbers/8.png")
	elseif cCounter == 9 then
		scene.SetComponent(self.ID, "sprite", "../Textures/Numbers/9.png")
	else	
		scene.SetComponent(self.ID, "sprite", "../Textures/Numbers/0.png")
	end
end
return coinCounter