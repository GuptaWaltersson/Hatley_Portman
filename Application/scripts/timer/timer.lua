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
