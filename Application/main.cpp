
#include <raylib.h>

#include <iostream>
#include <thread>
#include <string>

#include "lua.hpp"
#include "entt.hpp"
#include "ecs/registry.hpp"
#include "ecs/scene.hpp"
#include "ecs/components.hpp"


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

class PoisonSystem : public System {
	int m_lifetime;

public:
	PoisonSystem(int lifetime) : m_lifetime(lifetime) {}

	bool OnUpdate(entt::registry& registry, float delta) final {
		auto view = registry.view<Health, Poison>();
		view.each([](Health& health, const Poison& poison) {
			health.value -= poison.tickDamage;
			});

		return (--m_lifetime) <= 0;
	}
};

class CleanupSystem : public System {
public:
	bool OnUpdate(entt::registry& registry, float delta) final {
		auto view = registry.view<Health>();
		view.each([&](entt::entity entity, const Health& health) {
			if (health.value <= 0.f) {
				registry.destroy(entity);
			}
			});
		return false;
	}
};

class InfoSystem : public System {
	int m_updateCounter = 0;

public:
	InfoSystem() = default;

	bool OnUpdate(entt::registry& registry, float delta) final {
		int count = registry.view<entt::entity>().size();
		auto healthView = registry.view<Health>();
		auto poisonView = registry.view<Poison>();
		printf("\n-- Update %i --\n", ++m_updateCounter);
		printf("Living entities:\t%i\n", static_cast<int>(healthView.size()));
		printf("Poisoned entities:\t%i\n", static_cast<int>(poisonView.size()));

		return false;
	}
};

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	Scene scene(L);
	Scene::lua_openScene(L, &scene);

	scene.CreateSystem<PoisonSystem>(5);
	scene.CreateSystem<CleanupSystem>();
	scene.CreateSystem<InfoSystem>();
	luaL_dofile(L, "scripts/sceneDemo.lua");

	for (int i = 0; i < 10; ++i)
	{
		scene.UpdateSystems(1);
	}

	//std::thread consolethread(ConsoleThreadFunction, L);
	const int screenWidth = 1600;
	const int screenHeight = 900;
	const int scale = 8;
	InitWindow(screenWidth, screenHeight, "Hatley Portman");
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
