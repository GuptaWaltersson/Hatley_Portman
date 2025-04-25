
#include <raylib.h>

#include <iostream>

#include <thread>
#include <string>

#include "Player/player.h"
#include "Player/playerScriptingBridge.h"

#include "lua.hpp"
#include "entt.hpp"
#include "ecs/scene.hpp"
#include "ecs/components.hpp"
#include "ecs/systems.hpp"

void DumpError(lua_State* L)
{
	if (lua_gettop(L) && lua_isstring(L, -1))
	{
		std::cout << "Lua error: " << lua_tostring(L, -1) << std::endl;
		lua_pop(L, 1);
	}
}

void ConsoleThreadFunction(lua_State* L)
{
	std::string input;
	while (!WindowShouldClose()) 
	{
		std::cout << "> ";
		std::getline(std::cin, input);

		if (luaL_dostring(L, input.c_str()) != LUA_OK);
		{
			DumpError(L);
		}
	}
}

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	Scene scene(L);
	Scene::lua_openScene(L, &scene);

	//scene.CreateSystem<PoisonSystem>(5);
	//scene.CreateSystem<CleanupSystem>();
	//scene.CreateSystem<InfoSystem>();
	scene.CreateSystem<SpriteSystem>();
	//luaL_dofile(L, "scripts/sceneDemo.lua");
	luaL_dofile(L, "scripts/player.lua");
	scene.CreateSystem<GravitySystem>(9.8);
	scene.CreateSystem<MovementSystem>();
	//scene.CreateSystem<InfoSystem>();
	luaL_dofile(L, "scripts/sceneDemo.lua");
	
	
	for (int i = 0; i < 10; ++i)
	{
		scene.UpdateSystems(1);
	}
	Vector2 pos = scene.GetPlayerPosition();
	//printf(std::to_string(scene.GetEntityCount()).c_str());

	//std::thread consolethread(ConsoleThreadFunction, L);
	const int screenWidth = 1600;
	const int screenHeight = 900;
	const int scale = 8;

	InitWindow(screenWidth, screenHeight, "Hatman");
	
	//std::string texturePath = "../Textures/Portman_v1.png";

	//Texture2D Jonas = LoadTexture(texturePath.c_str());
	//float framewidth = Jonas.width;
	//float frameheight = Jonas.height;

	//// what part of the picture we use for drawing
	//// we can use this to create bitmaps and animate that way
	//Rectangle source = { 0.0,0.0, framewidth, frameheight }; 
	//
	////Defines the place for rectangle the picture fills
	////first two x,y coordinates other two are size of picture width and height
	//Rectangle destrec = { screenWidth / 2, screenHeight / 2, framewidth * scale, frameheight * scale}; 

	////Defines origin of the picture, so if rotate then rotate around this point
	//Vector2 origin = { framewidth, frameheight };

	SetTargetFPS(60);


	bool running = true;
	while (!WindowShouldClose())
	{
		//Check to load lua file
		/*if (luaL_dofile(L, "scripts/config.lua") != LUA_OK) {
			lua_pop(L, 1);
		} */

		//change texture if needed i guess, remember to change to a texture the same size otherwise we have to also update the source dest rec
		//scene.UpdateSystems(1);
		scene.UpdateSystems(1);
		Vector2 pos = scene.GetPlayerPosition();
		destrec.x = pos.x;
		destrec.y = pos.y;

		// DRAW
		BeginDrawing();
		ClearBackground(RAYWHITE);
		
		scene.UpdateSystems(1);
		//DrawTexturePro(Jonas, source, destrec, origin, 0.0f, WHITE);
		/*DrawLine((int)destrec.x, 0, (int)destrec.x, screenHeight, GRAY);
		DrawLine(0, (int)destrec.y, screenWidth, (int)destrec.y, GRAY);*/

		DrawText("The Gupt is Gupting", 190, 200, 20, BLACK);

		EndDrawing();
	}
	//UnloadTexture(Jonas);

	CloseWindow();
	lua_close(L);
	return 0;
}
