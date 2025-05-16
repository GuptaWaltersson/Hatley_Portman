#pragma once

#include "entt.hpp"
#include "lua.hpp"
#include "components.hpp"

class SceneManager {
public:
	SceneManager(lua_State* L, entt::registry& registry) : m_L(L), m_registry(registry) {}
	~SceneManager() = default;
	
	void Save();
	void Load();
private:
	entt::registry& m_registry;
	lua_State* m_L;
};