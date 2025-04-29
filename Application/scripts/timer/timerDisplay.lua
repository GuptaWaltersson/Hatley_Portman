local timer = require("scripts/timer/timer")
local display = {}

function timerDisplay.OnUpdate(self, delta)
    -- Accumulate elapsed time
    self.time = (self.time or 0) + delta

    local totalMilliseconds = math.floor(self.time * 1000)
    local minutes = math.floor(totalMilliseconds / 60000)
    local seconds = math.floor((totalMilliseconds % 60000) / 1000)
    local millis = math.floor((totalMilliseconds % 1000) / 10)

    local formatted = string.format("%02d%02d%02d", minutes, seconds, millis)

    for i = 1, 6 do
        local digit = tonumber(formatted:sub(i, i))
        local entity = self.digits[i]
        if entity then
            local spritePath = string.format("../Textures/Numbers/%d.png", 9 + digit)
            scene.SetComponent(entity, "sprite", spritePath)
        end
    end
end


return display
