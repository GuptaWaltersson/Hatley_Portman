#pragma once

#include "lua.hpp"
#include "entt.hpp"
#include "components.hpp"

class System
{
public:
	virtual bool OnUpdate(entt::registry& registry, float delta) = 0;
};

class SpriteSystem : public System 
{
public:
	bool OnUpdate(entt::registry& registry, float delta) final {
		auto view = registry.view<Sprite>();
		std::cout << "Entities with Sprite: " << view.size() << std::endl;
		view.each([](const Sprite& sprite) {

			Rectangle source = { 0.0,0.0, sprite.texture.width, sprite.texture.height};
			Rectangle destrec = { 500, 100, sprite.texture.width * 8, sprite.texture.height * 8 };
			Vector2 origin = { sprite.texture.width, sprite.texture.height};

			DrawTexturePro(sprite.texture, source, destrec, origin, 0.0f, WHITE);
		
		});
		return false;
	}
};

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

class MovementSystem : public System {

public:
	bool OnUpdate(entt::registry& registry, float delta) final {
		auto view = registry.view<Position, Velocity>();
		view.each([&](Position& pos, const Velocity& velocity) {
			if (IsKeyDown(KEY_LEFT))
			{
				pos.x -= velocity.dx;
			}
			if (IsKeyDown(KEY_RIGHT))
			{
				pos.x += velocity.dx;
			}
			if (IsKeyPressed(KEY_SPACE))
			{
				//Jump operation
			}
			
		});
		return false;
	}
};

class GravitySystem : public System {
	float m_acceleration;
public :
	GravitySystem(float acceleration) : m_acceleration(acceleration){}

	bool OnUpdate(entt::registry& registry, float delta) final {
		auto view = registry.view<Velocity, Gravity>();
		view.each([&](Velocity& vel, const Gravity& acceleration) {
			vel.dy += acceleration.acceleration * delta;
			});
		return false;
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
		auto gravityView = registry.view<Gravity>();
		auto positionView = registry.view<Position>();
		printf("\n-- Update %i --\n", ++m_updateCounter);
		printf("Living entities:\t%i\n", static_cast<int>(healthView.size()));
		printf("Poisoned entities:\t%i\n", static_cast<int>(poisonView.size()));
		printf("Gravity entitie: \t%i\n", static_cast<int>(gravityView.size()));
		printf("position entitie: \t%i\n", static_cast<int>(positionView.size()));

		return false;
	}
};

class BehaviourSystem : public System 
{
	lua_State* m_L;
public:
	BehaviourSystem(lua_State* L) : m_L(L) {}

	bool OnUpdate(entt::registry& registry, float delta) final
	{
		auto view = registry.view<Behaviour>();

		view.each([&](Behaviour& script) {
			lua_rawgeti(m_L, LUA_REGISTRYINDEX, script.LuaTableRef);
			lua_getfield(m_L, -1, "OnUpdate");
			lua_pushvalue(m_L, -2);
			lua_pushnumber(m_L, delta);

			if (lua_pcall(m_L, 2, 0, 0) != LUA_OK)
			{
				if (lua_gettop(m_L) && lua_isstring(m_L, -1))
				{
					std::cout << "Lua error: " << lua_tostring(m_L, -1) << std::endl;
					lua_pop(m_L, 1);
				}
				lua_pop(m_L, 1);
			}
		});
	}
};
