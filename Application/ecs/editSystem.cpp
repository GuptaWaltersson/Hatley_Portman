#include "editSystem.hpp"


void EditingSystem::SelectObject()
{
    Vector2 mousePos = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        auto view = m_registry.view<Position, BBox>();
        view.each([&](entt::entity entity, Position& pos, BBox& box) {

            if (CheckCollisionPointRec(mousePos, { pos.x, pos.y, box.width, box.height })) {
				m_selectedEntity = entity;
            }
         });
    }

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && m_selectedEntity.has_value())
    {
		Position& pos = m_registry.get<Position>(m_selectedEntity.value());
		BBox& box = m_registry.get<BBox>(m_selectedEntity.value());
		pos.x = mousePos.x - box.width / 2;
		pos.y = mousePos.y - box.height / 2;
    }
    else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        m_selectedEntity.reset();
    }


}

void EditingSystem::CreateCloud(float xPos, float yPos, int width)
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

void EditingSystem::CreateTree(float xPos, float yPos, int width, int height)
{
	lua_getglobal(m_L, "block");
	lua_getfield(m_L, -1, "createTree");

	lua_pushnumber(m_L, width);
	lua_pushnumber(m_L, height);
	lua_pushnumber(m_L, xPos);
	lua_pushnumber(m_L, yPos);

	if (lua_pcall(m_L, 4, 0, 0) != LUA_OK)
	{
		lua_pop(m_L, 1);
	}
}
