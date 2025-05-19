-- Scene

local hatEntity = scene.CreateEntity()
scene.SetComponent(hatEntity,"behaviour","scripts/hat.lua")

local playerEntity = scene.CreateEntity()
scene.SetComponent(playerEntity, "behaviour", "scripts/player.lua")

local cloudEntity = scene.CreateEntity()
scene.SetComponent(cloudEntity,"behaviour","scripts/cloud.lua")
scene.SetComponent(cloudEntity,"tag","cloudManager")

coinManager = require("scripts.coin.coinManager")
coinManager.CreateEditManager()

local blockEntity = scene.CreateEntity()
scene.SetComponent(blockEntity,"behaviour","scripts/editingBlock.lua")

block = require("scripts.editingBlock")
block.Ground()





