#pragma once

#include "lua.hpp"
#include "entt.hpp"
#include "components.hpp"

class Editing
{
public:
	virtual bool OnEdit(float xPos, float yPos, int width, int height) = 0;
};

class CloudSystem : public Editing
{
	lua_State* m_L;
public:
	CloudSystem(lua_State* L) : m_L(L) {}

	bool OnEdit(float xPos,float yPos, float width, float height)
	{
		lua_getglobal(m_L, "createCloud");

		Vector2 mousePos = GetMousePosition();
		
		lua_pushnumber(m_L, width);
		lua_pushnumber(m_L, xPos);
		lua_pushnumber(m_L, yPos);
		if (lua_pcall(m_L, 3, 0, 0) != LUA_OK)
		{
			std::cerr << "Lua error: " << lua_tostring(m_L, -1) << std::endl;
			lua_pop(m_L, 1);
		}
		return false;
	}
};


