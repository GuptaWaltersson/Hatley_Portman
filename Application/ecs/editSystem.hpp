#pragma once

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

    void SelectObject();

    void CreateCloud(float xPos, float yPos, int width);
    void CreateTree(float xPos, float yPos, int width, int height);
    void CreateCoin(float xPos, float yPos);
};
