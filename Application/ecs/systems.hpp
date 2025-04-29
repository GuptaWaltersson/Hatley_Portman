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
			Rectangle destrec = { pos.x, pos.y, sprite.texture.width * sprite.scale, sprite.texture.height * sprite.scale };
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
		auto view = registry.view<Position, BBox>();
		view.each([&](Position& pos, BBox& box) {
			auto plaView = registry.view<Position, BBox, PlayerTag>();
			
			auto playerEntity = plaView.front();
			Position& playerPos = registry.get<Position>(playerEntity);
			Movement& playerVel = registry.get<Movement>(playerEntity);
			BBox& playerBox = registry.get<BBox>(playerEntity);

			Rectangle playerRect = { playerPos.x, playerPos.y, playerBox.width, playerBox.height };

			if (playerPos.x != pos.x && playerPos.y != pos.y)
			{

				Rectangle otherRect = { pos.x, pos.y, box.width, box.height };

				if (CheckCollisionRecs(playerRect, otherRect))
				{
					Rectangle collision = GetCollisionRec(playerRect, otherRect);

					// Calculate centers
					float playerCenterX = playerPos.x + playerBox.width / 2.0f;
					float playerCenterY = playerPos.y + playerBox.height / 2.0f;
					float blockCenterX = pos.x + box.width / 2.0f;
					float blockCenterY = pos.y + box.height / 2.0f;

					if (collision.width <= collision.height)
					{
						if (playerCenterX < blockCenterX)
						{
							playerPos.x -= collision.width;
							//std::cout << "LEFT" << std::endl;
							playerVel.dx = 0;
						}
						else
						{
							playerPos.x += collision.width;
							//std::cout << "RIGHT" << std::endl;
							playerVel.dx = 0;
						}
						
					}
					else
					{
						if (playerCenterY < blockCenterY)
						{
							playerPos.y -= collision.height;
							//std::cout << "TOP" << std::endl;
							playerVel.dy = 0;
							playerVel.canJump = true;
						}
						else
						{
							playerPos.y += collision.height;
							//std::cout << "BOTTOM" << std::endl;
						}
					}
						
				}
			}
		});
		return false;
	}
};

class MovementSystem : public System {

public:
	bool OnUpdate(entt::registry& registry, float delta) final {
		auto view = registry.view<Position, Movement, PlayerTag>();
		auto hatEntity = registry.view<HatTag, LastMove>().front();
		LastMove& LMove = registry.get<LastMove>(hatEntity);
		view.each([&](Position& pos, Movement& velocity, PlayerTag& pTag) {
			if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_A) || IsKeyDown(KEY_D))
			{
				if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
				{
					if (velocity.dx > -600)
					{
						velocity.dx -= velocity.ax * delta;
					}
					LMove.lastKey = "left";
				}
				if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
				{
					if (velocity.dx < 600)
					{
						velocity.dx += velocity.ax * delta;
					}
					LMove.lastKey = "right";
				}
			}
			else
			{
				if (velocity.dx < -100) {
					velocity.dx += velocity.ax *3/4 * delta;
				}
				else if (velocity.dx > 100) {
					velocity.dx -= velocity.ax *3/4 * delta;
				}
				else {
					velocity.dx = 0;
				}
			}


			if (IsKeyPressed(KEY_SPACE) && velocity.canJump)
			{
				velocity.dy -= velocity.ay;
				pos.y += velocity.dy * delta;

				velocity.canJump = false;
			}
			else if (pos.y >= 1000)
			{
				pos.y = 700;
				velocity.dy = 0;
			}
			

			pos.x += velocity.dx*delta;
			

			
		});
		return false;
	}
};

class GravitySystem : public System {
	float m_acceleration;
public :
	GravitySystem(float acceleration) : m_acceleration(acceleration){}

	bool OnUpdate(entt::registry& registry, float delta) final {
		auto view = registry.view<Movement, Gravity,Position>();
		view.each([&](Movement& vel, const Gravity& acceleration,Position& pos) {
			vel.dy += acceleration.acceleration * delta;
			pos.y += vel.dy * delta;
			});
		return false;
	}
};

class HatSystem : public System {
	lua_State* m_L;
public:
	HatSystem(lua_State* L) : m_L(L){}
	bool OnUpdate(entt::registry& registry, float delta) final {
		auto view = registry.view<HatTag, Position,Behaviour>();
		auto playerEntity = registry.view<Position, PlayerTag>().front();
		Position& playerPos = registry.get<Position>(playerEntity);

		view.each([&](HatTag& htag, Position& pos, Behaviour& script ) {

			if (htag.hatType == 0) // hat is on head
			{
				pos.x = playerPos.x;
				pos.y = playerPos.y;
			}
			
			if (IsKeyPressed(KEY_Q) && htag.hatType != 0)
			{
				htag.hatType = 0;
			}
			else if (IsKeyPressed(KEY_Q))
			{
				htag.hatType = 1;
				lua_rawgeti(m_L, LUA_REGISTRYINDEX, script.LuaTableRef);
				lua_getfield(m_L, -1, "throw");
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

			}

			if (IsKeyPressed(KEY_E) && htag.hatType != 0)
			{
				playerPos.x = pos.x;
				playerPos.y = pos.y;
				htag.hatType = 0;
			}
			
				// Get the function from lua and call it with delta time as argument
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
		return false;
	}
};

class InfoSystem : public System
{
public:
	bool OnUpdate(entt::registry& registry, float delta) final
	{
		auto gravityView = registry.view<Gravity>();
		auto playertagView = registry.view<PlayerTag>();
		printf("\n----update---\n");
		printf("gravityentitites: \t%i\n", gravityView.size());
		printf("player entities: \t%i\n", playertagView.size());

		return false;
	}


};
