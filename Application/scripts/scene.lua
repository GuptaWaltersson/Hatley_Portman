-- Scene

local hatEntity = scene.CreateEntity()
scene.SetComponent(hatEntity,"behaviour","scripts/hat.lua")

local playerEntity = scene.CreateEntity()
scene.SetComponent(playerEntity, "behaviour", "scripts/player.lua")

local cloudEntity = scene.CreateEntity()
scene.SetComponent(cloudEntity,"behaviour","scripts/cloud.lua")
scene.SetComponent(cloudEntity,"tag","cloudManager")

block = require("scripts.editingBlock")
block.Ground()

coinManager = require("scripts.coin.coinManager")
coinManager.CreateSceneManager()