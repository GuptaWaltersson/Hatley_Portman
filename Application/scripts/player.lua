local player {}

-- Compontents
player.position = {x = 0, y = 0},
player.sprite = {texture = "../Textures/Portman_v1.png"}


-- Behaviours
function player.OnCreate(self)
	print("Player created!")
	scene.SetComponent(self.ID, "position", {x = 200, y = 100})
end

function player.OnUpdate(delta)
	local dx, dy = 0, 0

	if scene.IsKeyPressed("A") then dx = dx - 10 end
	if scene.IsKeyPressed("D") then dx = dx + 10 end
	if scene.IsKeyPressed("W") then dy = dy - 1 end
	if scene.IsKeyPressed("S") then dy = dy + 1 end

	local pos = scene.GetComponent(self.ID, "position"))
	pos.x = pos.x + dx
	pos.y = pos.y + dy

	scene.SetComponent(self.ID, "position", pos)
end

return player