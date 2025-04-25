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
		auto view = registry.view<Sprite,Position>();

		view.each([](const Sprite& sprite, const Position& pos) {

			Rectangle source = { 0.0,0.0, sprite.texture.width, sprite.texture.height};
			Rectangle destrec = { pos.x, pos.y, sprite.texture.width * 4, sprite.texture.height * 4 };
			Vector2 origin = { sprite.texture.width, sprite.texture.height};
			   
			DrawTexturePro(sprite.texture, source, destrec, origin, 0.0f, WHITE);
		
		});
		return false;
	}
};

class CollisionSystem : public System
{
	bool OnUpdate(entt::registry& registry, float delta) final
	{
		auto playerEntity = registry.view<Position, BBox>().front();
		Position playerPos = registry.get<Position>(playerEntity);
		BBox playerBox = registry.get<BBox>(playerEntity);

		auto view = registry.view<Position, BBox>();
		view.each([&](Position& pos, BBox& box) {
			if (playerPos.x != pos.x && playerPos.x != pos.y) // Skip the player entity
			{
				if (CheckCollisionRecs({ playerPos.x, playerPos.y, playerBox.width, playerBox.height }, { pos.x, pos.y, box.width, box.height }))
				{
					// Handle collision
					std::cout << "Collision detected!" << std::endl;
				}
			}
			});
		return false;
	}
};

class MovementSystem : public System {

public:
	bool OnUpdate(entt::registry& registry, float delta) final {
		auto view = registry.view<Position, Velocity>();
		view.each([&](Position& pos, const Velocity& velocity) {
			if (IsKeyDown('A'))
			{
				pos.x -= velocity.dx;
			}
			if (IsKeyDown('D'))
			{
				pos.x += velocity.dx;
			}
			if (IsKeyDown('W'))
			{
				pos.y -= velocity.dy;
			}
			if (IsKeyDown('S'))
			{
				pos.y += velocity.dy;
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
