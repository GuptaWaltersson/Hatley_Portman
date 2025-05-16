#pragma once
#include <iostream>
#include "lua.hpp"
#include "entt.hpp"
#include "components.hpp"
#include <optional>

class EditingSystem {
    lua_State* m_L;
    entt::registry& m_registry;
	std::optional<entt::entity> m_selectedEntity;

public:
    EditingSystem(lua_State* L, entt::registry& registry)
        : m_L(L), m_registry(registry) {
    }

    void SelectEntity();

    void CreateCloud(float xPos, float yPos, int width);
    void CreateTree(float xPos, float yPos, int width, int height);
    void CreateCoin(float xPos, float yPos);
	void CreateBigMushroom(float xPos, float yPos, int width);
    void CreateMovingCloud(float xPos, float yPos, int width,int speed,float duration, float waitTime);
    void ChangeHatThrow(int HatThrow);
    void ChangePlayerPosition(float xPos, float yPos);
private:
	void MoveEntity(Vector2 mousePos);

    
};
