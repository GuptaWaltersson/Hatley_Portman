#include "editSystem.hpp"


void EditingSystem::SelectEntity()
{
    Vector2 mousePos = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        auto view = m_registry.view<Position, BBox>();
        view.each([&](entt::entity entity, Position& pos, BBox& box) {
            if (CheckCollisionPointRec(mousePos, { pos.x, pos.y, box.width, box.height }) && pos.y < 836) {
				m_selectedEntity = entity;
            }
         });
    }

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && m_selectedEntity.has_value())
    {
		MoveEntity(mousePos);
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

void EditingSystem::MoveEntity(Vector2 mousePos)
{
	auto selected = m_selectedEntity.value();

	Position& targetPos = m_registry.get<Position>(selected);
	BBox& targetBox = m_registry.get<BBox>(selected);
	float newX = mousePos.x - targetBox.width / 2;
	float newY = mousePos.y - targetBox.height / 2;

	if (m_registry.any_of<GroupID>(selected)) {
		int id = m_registry.get<GroupID>(selected).id;

		auto view = m_registry.view<Position, BBox, GroupID>();
		view.each([&](entt::entity entity, Position& pos, BBox& box, GroupID& groupId) {
			if (groupId.id == id && entity != selected) {
				Position& otherPos = m_registry.get<Position>(entity);
				BBox& otherBox = m_registry.get<BBox>(entity);

				float offsetX = otherPos.x - targetPos.x;
				float offsetY = otherPos.y - targetPos.y;
				
				otherPos.x = newX + offsetX;
				otherPos.y = newY + offsetY;

			}
		});
	}


	Position& pos = m_registry.get<Position>(m_selectedEntity.value());
	BBox& box = m_registry.get<BBox>(m_selectedEntity.value());
	pos.x = mousePos.x - box.width / 2;
	pos.y = mousePos.y - box.height / 2;
	if (pos.y > 782) pos.y = 782;
	if (pos.y < 0) pos.y = 0;
	if (pos.x > 1610) pos.x = 1610;
	if (pos.x < 0) pos.x = 0;
}
