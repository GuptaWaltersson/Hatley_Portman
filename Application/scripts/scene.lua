-- Scene

local hatEntity = scene.CreateEntity()
scene.SetComponent(hatEntity,"behaviour","scripts/hat.lua")

local playerEntity = scene.CreateEntity()
scene.SetComponent(playerEntity, "behaviour", "scripts/player.lua")

coinManager = require("scripts.coin.coinManager")
coinManager.CreateSceneManager()

block = require("scripts.editingBlock")
block.Ground()
