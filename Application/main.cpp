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
#include "ecs/sceneManager.hpp"

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
	SceneManager sceneManager(scene->m_registry);
	sceneManager.Load();

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

	EditingSystem edit(L, scene->m_registry);
	SceneManager sceneManager(scene->m_registry);

	LoadEditScene(L, scene);

	Rectangle CloudButton = { 280.0f, 850.0f, 120, 70 };
	Rectangle TreeButton = { 100.0f,850.0f,120,70 };
	Rectangle CoinButton = { 460.0f,850.0f,120,70 };
	Rectangle MushroomButton = { 640.0f,850.0f,150,70 };
	Rectangle HatButton = { 850.0f,850.0f,180,70 };
	Rectangle SaveButton = { 1400.0f,850.0f,120,70};

	bool running = true;
	while (running)
	{
		BeginDrawing();
		ClearBackground(SKYBLUE);
		Vector2 mousePos = GetMousePosition();
		float delta = GetFrameTime();
		scene->UpdateSystems(delta);

		DrawRectangleRec(CloudButton, WHITE);
		DrawText("Cloud", CloudButton.x + 5, CloudButton.y + 25, 20, BLACK);

		DrawRectangleRec(TreeButton, WHITE);
		DrawText("Tree", TreeButton.x + 5, TreeButton.y + 25, 20, BLACK);

		DrawRectangleRec(CoinButton, WHITE);
		DrawText("Coin", CoinButton.x + 5, CoinButton.y + 25, 20, BLACK);

		DrawRectangleRec(MushroomButton, WHITE);
		DrawText("Big Mushroom", MushroomButton.x + 5, MushroomButton.y + 25, 20, BLACK);

		DrawRectangleRec(HatButton, WHITE);
		DrawText("Hat: trajectory", HatButton.x + 5, HatButton.y + 25, 20, BLACK);

		DrawRectangleRec(SaveButton, WHITE);
		DrawText("Save", SaveButton.x + 5, SaveButton.y + 25, 20, BLACK);


		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			if (CheckCollisionPointRec(mousePos, CloudButton))
			{
				edit.CreateCloud(ScreenWidth / 2, ScreenHeight / 2, 4);
			}
			else if (CheckCollisionPointRec(mousePos, TreeButton))
			{
				edit.CreateTree(400, 400, 3, 2);
			}
			else if (CheckCollisionPointRec(mousePos, CoinButton))
			{
				edit.CreateCoin(700, 700);
			}
			else if (CheckCollisionPointRec(mousePos, MushroomButton))
			{
				edit.CreateBigMushroom(800, 300, 6);
			}
			else if (CheckCollisionPointRec(mousePos, SaveButton))
			{
				sceneManager.Save();
			}
		}

		if (IsKeyPressed(KEY_ESCAPE)) {
			gameState = GameState::StartMenu;
			running = false;
		}

		edit.SelectEntity();

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
	editingScene.CreateSystem<BehaviourSystem>(L);
	//editingScene.CreateSystem<MovementSystem>();
	//editingScene.CreateSystem<HatSystem>(L);
	//editingScene.CreateSystem<CollisionSystem>(L);
	//editingScene.CreateSystem<GravitySystem>(0.0);


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
