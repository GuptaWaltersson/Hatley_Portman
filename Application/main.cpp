
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
	const int screenWidth = 1600;
	const int screenHeight = 900;
	

	InitWindow(screenWidth, screenHeight, "Hatman");

	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	Scene scene(L);
	Scene::lua_openScene(L, &scene);

	scene.CreateSystem<SpriteSystem>();
	scene.CreateSystem<CollisionSystem>();
	scene.CreateSystem<GravitySystem>(9.8);
	scene.CreateSystem<MovementSystem>();
	if (luaL_dofile(L, "scripts/player.lua") != LUA_OK) {
		std::cerr << "Lua error: " << lua_tostring(L, -1) << std::endl;
		lua_pop(L, 1);
	}
	if (luaL_dofile(L, "scripts/block.lua") != LUA_OK) {
		std::cerr << "Lua error: " << lua_tostring(L, -1) << std::endl;
		lua_pop(L, 1);
	}


	bool running = true;
	while (!WindowShouldClose())
	{
		// DRAW
		BeginDrawing();
		ClearBackground(RAYWHITE);
		
		scene.UpdateSystems(1);

		DrawText("The Gupt is Gupting", 190, 200, 20, BLACK);

		EndDrawing();
	}

	CloseWindow();
	lua_close(L);
	return 0;
}
