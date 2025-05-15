#include "editSystem.hpp"
#include "json.hpp"
#include <fstream>
#include <iostream>

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

	if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
		auto view = m_registry.view<Position, BBox, Tag>();
		view.each([&](entt::entity entity, Position& pos, BBox& box, Tag& tag) {
			if (CheckCollisionPointRec(mousePos, { pos.x, pos.y, box.width, box.height }) && pos.y < 836) {
				if(tag.name != "player")
					m_registry.destroy(entity);
			}
		});
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
		std::cerr << "Lua error: " << lua_tostring(m_L, -1) <<" in create Cloud" << std::endl;
		lua_pop(m_L, 1);
	}
	lua_pop(m_L, 1);
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
		std::cout << "Lua error :" << lua_tostring(m_L, -1) << " in create Tree" << std::endl;
		lua_pop(m_L, 1);
	}
	lua_pop(m_L, 1);
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
		std::string name = m_registry.get<Tag>(selected).name;

		auto view = m_registry.view<Position, GroupID, Tag>();
		view.each([&](entt::entity entity, Position& pos, GroupID& groupId, Tag& tag) {
			if (groupId.id == id && tag.name == name && entity != selected) {
				Position& otherPos = m_registry.get<Position>(entity);

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

}

void EditingSystem::CreateCoin(float xPos, float yPos)
{
	lua_getglobal(m_L, "coin");
	lua_getfield(m_L, -1, "CreateCoin");

	lua_pushnumber(m_L, xPos);
	lua_pushnumber(m_L, yPos);

	if (lua_pcall(m_L, 2, 0, 0) != LUA_OK)
	{
		std::cout << "Lua error: " << lua_tostring(m_L, -1)<< " in create coin" << std::endl;
		lua_pop(m_L, 1);
	}
	lua_pop(m_L, 1);
}

void EditingSystem::CreateBigMushroom(float xPos, float yPos, int width)
{
	lua_getglobal(m_L, "block");
	lua_getfield(m_L, -1, "createMushroom");

	lua_pushnumber(m_L, width);
	lua_pushnumber(m_L, xPos);
	lua_pushnumber(m_L, yPos);

	if (lua_pcall(m_L, 3, 0, 0) != LUA_OK)
	{
		std::cout << "Lua error: " << lua_tostring(m_L, -1) << " in create mushroom" << std::endl;
		lua_pop(m_L, 1);
	}
	lua_pop(m_L, 1);
}

void EditingSystem::CreateMovingCloud(float xPos, float yPos, int width,int speed, float duration)
{
	auto view = m_registry.view<Tag,Behaviour>();
	
	entt::entity cloudManagerEntity = entt::null;
	for (auto entity : view) {
		Tag& tag = m_registry.get<Tag>(entity);
		if (tag.name == "cloudManager") {
			cloudManagerEntity = entity;
			
		}
	}

	if (cloudManagerEntity != entt::null) {

		Behaviour& behaviour = m_registry.get<Behaviour>(cloudManagerEntity);

		lua_rawgeti(m_L, LUA_REGISTRYINDEX, behaviour.LuaTableRef); // Push the table
		lua_getfield(m_L, -1, "NewCloud"); // Get the NewCloud function
		lua_pushvalue(m_L, -2); // Push the table again as `self`

		lua_pushnumber(m_L, width);
		lua_pushnumber(m_L, xPos);
		lua_pushnumber(m_L, yPos);
		lua_pushnumber(m_L, speed);
		lua_pushnumber(m_L, duration);
		if (lua_pcall(m_L, 6, 0, 0) != LUA_OK)
		{
			std::cout << "Lua error: " << lua_tostring(m_L, -1) << " in create moving cloud" << std::endl;
			lua_pop(m_L, 1);
		}
		lua_pop(m_L, 1);
	}
	else {
		std::cout << "couldn't find cloudmanager" << std::endl;
	}


}


void EditingSystem::ChangeHatThrow(int HatThrow)
{
	auto hat = m_registry.view<HatTag,Behaviour>().front();
	Behaviour& script = m_registry.get<Behaviour>(hat);
	HatTag& htag = m_registry.get<HatTag>(hat);

	lua_rawgeti(m_L, LUA_REGISTRYINDEX, script.LuaTableRef);
	lua_getfield(m_L,-1,"newThrow");
	lua_pushvalue(m_L, -2);
	lua_pushnumber(m_L, HatThrow);

	if (lua_pcall(m_L, 2, 0, 0) != LUA_OK)
	{
		std::cout << "Lua error: " << lua_tostring(m_L, -1) << " in ChangeHatThrow" << std::endl;
		lua_pop(m_L, 1);
	}
	lua_pop(m_L, 1);
}

