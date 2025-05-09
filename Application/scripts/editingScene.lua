-- Scene

local hatEntity = scene.CreateEntity()
scene.SetComponent(hatEntity,"behaviour","scripts/hat.lua")

local playerEntity = scene.CreateEntity()
scene.SetComponent(playerEntity, "behaviour", "scripts/player.lua")


--dofile("scripts/coin/coinManager.lua")
dofile("scripts/hat.lua")
--dofile("scripts/editingBlock.lua")

local blockEntity = scene.CreateEntity()
scene.SetComponent(blockEntity,"behaviour","scripts/editingBlock.lua")

local block = require("scripts.editingBlock")
block.Ground()

block.createCloud(5, 500, 500)


