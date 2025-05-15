-- Scene

local hatEntity = scene.CreateEntity()
scene.SetComponent(hatEntity,"behaviour","scripts/hat.lua")

local playerEntity = scene.CreateEntity()
scene.SetComponent(playerEntity, "behaviour", "scripts/player.lua")

local cloudEntity = scene.CreateEntity()
scene.SetComponent(cloudEntity,"behaviour","scripts/cloud.lua")

--dofile("scripts/coin/coinManager.lua")
-- dofile("scripts/hat.lua")
--dofile("scripts/editingBlock.lua")

local blockEntity = scene.CreateEntity()
scene.SetComponent(blockEntity,"behaviour","scripts/editingBlock.lua")

block = require("scripts.editingBlock")
block.Ground()





