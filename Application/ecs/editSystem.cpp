#include "editSystem.hpp"

void EditingSystem::SelectObject()
{
}

void EditingSystem::CreateCloud(float xPos, float yPos, int width, int height)
{
	lua_getglobal(m_L, "block");
	lua_getfield(m_L, -1, "createCloud");


	lua_pushnumber(m_L, width);
	lua_pushnumber(m_L, xPos);
	lua_pushnumber(m_L, yPos);
	if (lua_pcall(m_L, 3, 0, 0) != LUA_OK)
	{
		//std::cerr << "Lua error: " << lua_tostring(m_L, -1) << std::endl;
		lua_pop(m_L, 1);
	}
	
}
