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

	Block CloudSettings;
	Block TreeSettings;
	Block MushroomSettings;

	bool ShowCloudSettings = false;
	bool ShowTreeSettings = false;
	bool ShowMushroomSettings = false;

	CloudSettings.width = 4;
	CloudSettings.speed = 100;
	CloudSettings.duration = 2.0f;
	CloudSettings.waitTime = 0.1f;

	int HatThrow = 1;
	int MaxAmountofThrows = 2;
	Rectangle TreeButton = { 100.0f,850.0f,100,70 };
	Rectangle TreeOption = { 210.0f,850.0f,30,70 };
	Rectangle CloudButton = { 280.0f, 850.0f, 120, 70 };
	Rectangle CloudOption = { 410.0f,850.0f,30,70 };
	Rectangle CoinButton = { 475.0f,850.0f,100,70 };
	Rectangle MushroomButton = { 640.0f,850.0f,150,70 };
	Rectangle MushroomOption = { 800.0f,850.0f,30,70 };
	Rectangle HatButton = { 850.0f,850.0f,180,70 };
	Rectangle SaveButton = { 1400.0f,850.0f,120,70};

	Rectangle SpeedText = {250.0f,790,80,50};
	Rectangle SpeedNumber = { 400.0f,790.0f,60,50 };
	Rectangle PlusSpeed = { 470.0f,790,50,50 };
	Rectangle MinusSpeed = { 340.0f,790,50,50 };

	Rectangle WaitText = { 250,730,80,50 };
	Rectangle WaitNumber = { 400,730,60,50 };
	Rectangle WaitPlus = { 470,730,50,50 };
	Rectangle WaitMinus = { 340,730,50,50 };

	Rectangle DurationText = { 250,670,80,50 };
	Rectangle DurationNumber = { 400,670,60,50 };
	Rectangle DurationPlus = { 470,670,50,50 };
	Rectangle DurationMinus = { 340,670,50,50 };

	Rectangle WidthText = { 250,610,80,50 };
	Rectangle WidthNumber = { 400,610,60,50 };
	Rectangle WidthPlus = { 470,610,50,50 };
	Rectangle WidthMinus = { 340,610,50,50 };


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
		DrawRectangleRec(CloudOption, WHITE);

		DrawRectangleRec(TreeButton, WHITE);
		DrawText("Tree", TreeButton.x + 5, TreeButton.y + 25, 20, BLACK);
		DrawRectangleRec(TreeOption, WHITE);
		DrawText("|",TreeOption.x+10,TreeOption.y+25,20,BLACK);
		DrawText("^", TreeOption.x + 5, TreeOption.y + 20, 40, BLACK);

		DrawRectangleRec(CoinButton, WHITE);
		DrawText("Coin", CoinButton.x + 5, CoinButton.y + 25, 20, BLACK);

		DrawRectangleRec(MushroomButton, WHITE);
		DrawText("Big Mushroom", MushroomButton.x + 5, MushroomButton.y + 25, 20, BLACK);
		DrawRectangleRec(MushroomOption, WHITE);

		DrawRectangleRec(HatButton, WHITE);
		if (HatThrow == 2)
		{
			DrawText("Hat: Trajectory", HatButton.x + 5, HatButton.y + 25, 20, BLACK);
		}
		else if (HatThrow == 1)
		{
			DrawText("Hat: Linear", HatButton.x + 5, HatButton.y + 25, 20, BLACK);
		}
		
		DrawRectangleRec(SaveButton, WHITE);
		DrawText("Save", SaveButton.x + 5, SaveButton.y + 25, 20, BLACK);

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			if (CheckCollisionPointRec(mousePos, CloudButton))
			{
				edit.CreateMovingCloud(
					ScreenWidth / 2, 
					ScreenHeight / 2,
					CloudSettings.width,
					CloudSettings.speed,
					CloudSettings.duration,
					CloudSettings.waitTime
				);
			}
			else if (CheckCollisionPointRec(mousePos, TreeButton))
			{
				edit.CreateTree(400, 400, 3, 2);
			}
			else if (CheckCollisionPointRec(mousePos, CoinButton))
			{
				//edit.CreateCoin(700, 700);
				//edit.ChangePlayerPosition(500, 500);
			}
			else if (CheckCollisionPointRec(mousePos, MushroomButton))
			{
				edit.CreateBigMushroom(800, 300, 6);
			}
			else if (CheckCollisionPointRec(mousePos, SaveButton))
			{
				sceneManager.Save();
			}
			else if (CheckCollisionPointRec(mousePos, HatButton))
			{
				if (HatThrow % MaxAmountofThrows != 0)
				{
					HatThrow++;
				}
				else
				{
					HatThrow = 1;
				}
				edit.ChangeHatThrow(HatThrow);
			}
			else if (CheckCollisionPointRec(mousePos, TreeOption))
			{

			}
			else if (CheckCollisionPointRec(mousePos, CloudOption))
			{
				ShowCloudSettings = true;
				
			}
			else if (CheckCollisionPointRec(mousePos, MushroomOption))
			{

			}
		}

		if (ShowCloudSettings)
		{
			// Speed
			DrawRectangleRec(SpeedText, WHITE);
			DrawText("Speed:", SpeedText.x + 5, SpeedText.y + 10, 20, BLACK);

			DrawRectangleRec(SpeedNumber, WHITE);
			const char* CloudSpeed = TextFormat(" % d", CloudSettings.speed);
			DrawText(CloudSpeed, SpeedNumber.x-18, SpeedNumber.y+10, 30, BLACK);

			DrawRectangleRec(PlusSpeed, WHITE);
			DrawText("+", PlusSpeed.x+15, PlusSpeed.y, 50, BLACK);

			DrawRectangleRec(MinusSpeed, WHITE);
			DrawText("-", MinusSpeed.x + 15, MinusSpeed.y, 50, BLACK);

			//Wait
			DrawRectangleRec(WaitText, WHITE);
			DrawText("Wait", WaitText.x + 5, WaitText.y + 10, 20, BLACK);

			DrawRectangleRec(WaitMinus, WHITE);
			DrawText("-", WaitMinus.x + 15, WaitMinus.y, 50, BLACK);

			DrawRectangleRec(WaitNumber, WHITE);
			const char* CloudWait = TextFormat("%.2f", CloudSettings.waitTime);
			DrawText(CloudWait, WaitNumber.x+2, WaitNumber.y + 10, 30, BLACK);

			DrawRectangleRec(WaitPlus, WHITE);
			DrawText("+", WaitPlus.x + 15, WaitPlus.y, 50, BLACK);

			//Duration
			DrawRectangleRec(DurationText, WHITE);
			DrawText("Duration", DurationText.x + 5, DurationText.y + 10, 20, BLACK);

			DrawRectangleRec(DurationMinus, WHITE);
			DrawText("-", DurationMinus.x + 15, DurationMinus.y, 50, BLACK);

			DrawRectangleRec(DurationNumber, WHITE);
			const char* CloudDuration = TextFormat("%.2f", CloudSettings.duration);
			DrawText(CloudDuration, DurationNumber.x + 2, DurationNumber.y + 10, 30, BLACK);

			DrawRectangleRec(DurationPlus, WHITE);
			DrawText("+", DurationPlus.x + 15, DurationPlus.y, 50, BLACK);

			//Width
			DrawRectangleRec(WidthText, WHITE);
			DrawText("Length: ", WidthText.x + 5, WidthText.y + 10, 20, BLACK);

			DrawRectangleRec(WidthMinus, WHITE);
			DrawText("-", WidthMinus.x + 15, WidthMinus.y, 50, BLACK);

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
