#pragma once

#include "entt.hpp"
#include "lua.hpp"
#include "components.hpp"

class SceneManager {
public:
	SceneManager(entt::registry& registry): m_registry(registry) {}
	~SceneManager() = default;
	
	void Save();
	void Load();
private:
	entt::registry& m_registry;
};