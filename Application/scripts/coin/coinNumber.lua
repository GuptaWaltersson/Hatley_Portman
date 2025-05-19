coinNumber = {}
-- Behaviours
function coinNumber.OnCreate(self)

end

function coinNumber.OnUpdate(self, delta)

end

function coinNumber.SetNumber(entity, numberOfCoin)
	local path = "../Textures/Numbers/" .. tostring(numberOfCoin) .. ".png"
	if numberOfCoin < 0 or numberOfCoin > 9 then
		path = "../Textures/Numbers/0.png"
	end
	scene.SetComponent(entity, "sprite", path)
end

return coinNumber