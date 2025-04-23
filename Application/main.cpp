#include <raylib.h>

#include <iostream>

#include <thread>
#include <string>

#include "Player/player.h"
#include "Player/playerScriptingBridge.h"

#include "lua.hpp"





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

	lua_State* LState = luaL_newstate();
	luaL_openlibs(LState);
	luaL_dofile(LState, "scripts/playerEntity.lua");
	lua_getglobal(LState, "entities");

	


	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	player user;
	playerScriptingBridge::bind(L, &user);

	
	//std::thread consolethread(ConsoleThreadFunction, L);
	const int screenWidth = 1600;
	const int screenHeight = 900;
	const int scale = 8;

	InitWindow(screenWidth, screenHeight, "Portal jonas");
	std::string texturePath = "../Textures/Portman_v1.png";

	Texture2D Jonas = LoadTexture(texturePath.c_str());
	float framewidth = Jonas.width;
	float frameheight = Jonas.height;

	// what part of the picture we use for drawing
	// we can use this to create bitmaps and animate that way
	Rectangle source = { 0.0,0.0, framewidth, frameheight }; 
	

	//Defines the place for rectangle the picture fills
	//first two x,y coordinates other two are size of picture width and height
	Rectangle destrec = { screenWidth / 2, screenHeight / 2, framewidth * scale, frameheight * scale}; 

	//Defines origin of the picture, so if rotate then rotate around this point
	Vector2 origin = { framewidth, frameheight };

	SetTargetFPS(60);

	bool running = true;
	while (!WindowShouldClose())
	{
		//Check to load lua file
		if (luaL_dofile(L, "scripts/config.lua") != LUA_OK) {
			lua_pop(L, 1);
		} 

		//change texture if needed i guess, remember to change to a texture the same size otherwise we have to also update the source dest rec
		if (texturePath != user.getTextureName()) //update only when new texture is writen in the lua file
		{
			Jonas = LoadTexture(user.getTextureName().c_str());
			texturePath = user.getTextureName();
		}
		float speed = user.getSpeed();
		std::string speedStr = std::to_string(speed);

//		float deltaTime = GetFrameTime();
		user.updatePlayer(0.0);
		destrec.x = user.getPositon().x;
		destrec.y = user.getPositon().y;

		// DRAW
		BeginDrawing();

		ClearBackground(RAYWHITE);
		//DrawTexture(Jonas, destrec.x, destrec.y, WHITE);
		DrawTexturePro(Jonas, source, destrec, origin, 0.0f, WHITE);
		DrawText(speedStr.c_str(), 190, 200, 20, BLACK);

		EndDrawing();
	}
	UnloadTexture(Jonas); // IMPORTANT	

	CloseWindow();

	std::cout << "Hello World!" << std::endl;
	return 0;
}