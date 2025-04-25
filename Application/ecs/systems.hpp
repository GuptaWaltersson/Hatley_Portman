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
			Rectangle destrec = { pos.x, pos.y, sprite.texture.width * 8, sprite.texture.height * 8 };
			Vector2 origin = { sprite.texture.width, sprite.texture.height};

			DrawTexturePro(sprite.texture, source, destrec, origin, 0.0f, WHITE);
		
		});
		return false;
	}
};


class MovementSystem : public System {

public:
	bool OnUpdate(entt::registry& registry, float delta) final {
		auto view = registry.view<Position, Velocity>();
		view.each([&](Position& pos, Velocity& velocity) {
			if (IsKeyDown(KEY_LEFT))
			{
				if (velocity.dx > -75)
				{
					velocity.dx -= 5*delta;
				}
			}
			else if (IsKeyDown(KEY_RIGHT))
			{
				if (velocity.dx < 75)
				{
					velocity.dx += 5*delta;
				}
			}
			else
			{
				velocity.dx = 0;
			}
			if (IsKeyPressed(KEY_SPACE))
			{
				velocity.dy -= 1000;
			}
			else if (pos.y >= 700)
			{
				pos.y = 700;
				velocity.dy = 0;
			}
			pos.x += velocity.dx*delta;
			pos.y += velocity.dy*delta;

			
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

class InfoSystem : public System
{
public:
	bool OnUpdate(entt::registry& registry, float delta) final
	{
		auto gravityView = registry.view<Gravity>();
		printf("\n----update---\n");
		printf("gravityentitites: \t%i\n", gravityView.size());

		return false;
	}


};
