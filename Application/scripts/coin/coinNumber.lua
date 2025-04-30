coinNumber = {}

-- Behaviours
function coinNumber.OnCreate(self)
	scene.SetComponent(self.ID, "tag", "counter")
	scene.SetComponent(self.ID, "position", {x=1530, y=30})

	if nrOfCoins == 1 then
		scene.SetComponent(self.ID, "sprite", "../Textures/Numbers/1.png")
	elseif nrOfCoins == 2 then
		scene.SetComponent(self.ID, "sprite", "../Textures/Numbers/2.png")
	elseif nrOfCoins == 3 then
		scene.SetComponent(self.ID, "sprite", "../Textures/Numbers/3.png")
	elseif nrOfCoins == 4 then
		scene.SetComponent(self.ID, "sprite", "../Textures/Numbers/4.png")
	elseif nrOfCoins == 5 then
		scene.SetComponent(self.ID, "sprite", "../Textures/Numbers/5.png")
	elseif nrOfCoins == 6 then
		scene.SetComponent(self.ID, "sprite", "../Textures/Numbers/6.png")
	elseif nrOfCoins == 7 then
		scene.SetComponent(self.ID, "sprite", "../Textures/Numbers/7.png")
	elseif nrOfCoins == 8 then
		scene.SetComponent(self.ID, "sprite", "../Textures/Numbers/8.png")
	elseif nrOfCoins == 9 then
		scene.SetComponent(self.ID, "sprite", "../Textures/Numbers/9.png")
	else	
		scene.SetComponent(self.ID, "sprite", "../Textures/Numbers/0.png")
	end
end

function coinNumber.OnUpdate(self, delta)

end

return coinNumber