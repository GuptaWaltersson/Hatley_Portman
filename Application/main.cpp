#include <raylib.h>

#include <iostream>

#include <thread>
#include <string>

#include "lua.hpp"
#include "entt.hpp"
#include "ecs/scene.hpp"
#include "ecs/components.hpp"
#include "ecs/systems.hpp"
#include "ecs/editSystem.hpp"

#define ScreenWidth 1656
#define ScreenHeight 936

enum class GameState
{
	StartMenu,
	EditingTool,
	Game,
	Quit
};
GameState gameState = GameState::StartMenu;

void LoadScene(lua_State* L, Scene* scene)
{
	scene->Clear();

	if (luaL_dofile(L, "scripts/scene.lua") != LUA_OK) {
		std::cerr << "Lua error: " << lua_tostring(L, -1) << std::endl;
		lua_pop(L, 1);
	}
}

void LoadEditScene(lua_State* L, Scene* scene)
{
	scene->Clear();

	if (luaL_dofile(L, "scripts/editingScene.lua") != LUA_OK) {
		std::cerr << "Editing Lua error: " << lua_tostring(L, -1) << std::endl;
		lua_pop(L, 1);
	}
}

void StartMenu(Scene* scene, lua_State* L)
{
	Rectangle playButton = { (float)(ScreenWidth / 2) - 100, (float)(ScreenHeight / 2) - 150, 200, 100 };
	Rectangle editingButton = { (float)(ScreenWidth / 2) - 100, (float)(ScreenHeight / 2), 200, 100 };
	Rectangle quitButton = { (float)(ScreenWidth / 2) - 100, (float)(ScreenHeight / 2) + 150, 200, 100 };

	bool running = true;
	while (running)
	{
		BeginDrawing();
		ClearBackground(SKYBLUE);
		DrawText("Hat-Trick", (float)(ScreenWidth / 2 - 220), 100, 100, WHITE);

		DrawRectangleRec(playButton, WHITE);
		DrawText("Play", playButton.x + 25, playButton.y + 25, 20, BLACK);

		DrawRectangleRec(editingButton, WHITE);
		DrawText("Edit", editingButton.x + 25, editingButton.y + 25, 20, BLACK);

		DrawRectangleRec(quitButton, WHITE);
		DrawText("Quit", quitButton.x + 25, quitButton.y + 25, 20, BLACK);

		Vector2 mousePos = GetMousePosition();

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			if (CheckCollisionPointRec(mousePos, playButton))
			{
				gameState = GameState::Game;
			}
			else if (CheckCollisionPointRec(mousePos, editingButton))
			{
				gameState = GameState::EditingTool;
			}
			else if (CheckCollisionPointRec(mousePos, quitButton))
			{
				gameState = GameState::Quit;
			}
			running = false;
		}

		EndDrawing();
	}

}

void EditingTool(Scene* scene, lua_State* L)
{
	Scene::lua_openScene(L, scene);
	CloudSystem cloudSys(L);
	LoadEditScene(L, scene);

	Rectangle addButton = { 100.0f, 100.0f, 200, 100 };

	bool running = true;
	while (running)
	{
		BeginDrawing();
		ClearBackground(SKYBLUE);

		Vector2 mousePos = GetMousePosition();

		DrawRectangleRec(addButton, WHITE);
		DrawText("add", addButton.x + 25, addButton.y + 25, 20, BLACK);
		
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			if (CheckCollisionPointRec(mousePos, addButton))
			{
				cloudSys.OnEdit(500, 500, 3, 3);
			}
		}

		if (IsKeyPressed(KEY_ESCAPE)) {
			gameState = GameState::StartMenu;
			running = false;
		}
		float delta = GetFrameTime();
		scene->UpdateSystems(delta);

		EndDrawing();
	}
	scene->Clear();
}

void GameLoop(Scene* scene, lua_State* L)
{
	Scene::lua_openScene(L, scene);

	LoadScene(L, scene);

	bool running = true;
	while (running)
	{
		BeginDrawing();
		ClearBackground(SKYBLUE);

		if (IsKeyPressed(KEY_ENTER))
			LoadScene(L, scene);

		if (IsKeyPressed(KEY_ESCAPE)) {
			gameState = GameState::StartMenu;
			running = false;
		}

		float delta = GetFrameTime();
		scene->UpdateSystems(delta);

		EndDrawing();
	}
	
	scene->Clear();
}

int main()
{
	InitWindow(ScreenWidth, ScreenHeight, "Hat-Trick");

	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	Scene startScene(L);
	Scene editingScene(L);
	Scene gameScene(L);

	gameScene.CreateSystem<SpriteSystem>();
	gameScene.CreateSystem<CollisionSystem>(L);
	gameScene.CreateSystem<GravitySystem>(9.8);
	gameScene.CreateSystem<MovementSystem>();
	gameScene.CreateSystem<BehaviourSystem>(L);
	gameScene.CreateSystem<HatSystem>(L);

	editingScene.CreateSystem<SpriteSystem>();
	editingScene.CreateSystem<MovementSystem>();
	editingScene.CreateSystem<CollisionSystem>(L);
	editingScene.CreateSystem<BehaviourSystem>(L);
	editingScene.CreateSystem<HatSystem>(L);
	editingScene.CreateSystem<GravitySystem>(0.0);
	
	


	bool running = true;
	while (running)
	{
		if (gameState == GameState::StartMenu)
		{
			StartMenu(&startScene, L);
		}
		else if (gameState == GameState::EditingTool)
		{
			EditingTool(&editingScene, L);
		}
		else if (gameState == GameState::Game)
		{
			GameLoop(&gameScene, L);
		} 
		else if (gameState == GameState::Quit)
		{
			running = false;
		}
	}


	

	CloseWindow();
	lua_close(L);
	return 0;
}
