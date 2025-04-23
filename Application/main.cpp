
#include <raylib.h>

#include <iostream>
#include <thread>
#include <string>

#include "lua.hpp"
#include "entt.hpp"
#include "ecs/registry.hpp"


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

	auto& registry = ECSRegistry::instance().getRegistry();

	//std::thread consolethread(ConsoleThreadFunction, L);
	const int screenWidth = 1600;
	const int screenHeight = 900;
	const int scale = 8;
	InitWindow(screenWidth, screenHeight, "Portal jonas");
	SetTargetFPS(60);


	bool running = true;
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		

		DrawText("We have something here?", 190, 200, 20, BLACK);

		EndDrawing();
	}



	CloseWindow();
	lua_close(L);
	return 0;
}


////Texture2D Jonas = LoadTexture("../Textures/Portman_v1.png");
//Texture2D Jonas = LoadTexture("../Textures/Pixel_Plattformer_Standard/Tiles/tile_0006.png");
//float framewidth = Jonas.width;
//float frameheight = Jonas.height;
//
//Rectangle source = { 0.0,0.0, framewidth, frameheight };
//
//Rectangle destrec = { screenWidth / 2, screenHeight / 2, framewidth * scale, frameheight * scale };
//
//Vector2 origin = { framewidth, frameheight };
//DrawTexturePro(Jonas, source, destrec, origin, 0.0f, WHITE);