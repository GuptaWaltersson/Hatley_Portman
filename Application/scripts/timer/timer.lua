local timer = {}
timer.time = 0

function timer.OnUpdate(self, delta)
    timer.time = timer.time + delta
    -- print(timer.time)
end

function timer.GetTime()
    return timer.time
end

return timer

--local timerEntity = scene.CreateEntity()
--scene.SetComponent(timerEntity, "behaviour", "scripts/timer/timer.lua")

--local timerDisplayEntity = scene.CreateEntity()
--scene.SetComponent(timerDisplayEntity, "behaviour", "scripts/timer/timerDisplay.lua")

--local digitEntities = {}

--for i = 1, 7 do
--    local digit = scene.CreateEntity()
--    scene.SetComponent(digit, "sprite", "../Textures/Numbers/0.png")
--    scene.SetComponent(digit, "position", { x = 500 + i * 50, y = 30 })
--    table.insert(digitEntities, digit)
--end

--scene.SetComponent(timerDisplayEntity, "behaviour", "scripts/timer/timerDisplay.lua")
--local b = scene.GetComponent(timerDisplayEntity, "behaviour")
--b.digits = digitEntities