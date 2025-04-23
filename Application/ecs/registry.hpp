#pragma once

#include <entt.hpp>
#include <cstdint>

class ECSRegistry
{

public:
	ECSRegistry() = default;
	~ECSRegistry() = default;

	static ECSRegistry& instance(); //Singleton pattern
	entt::registry& getRegistry();

	uint32_t createEntity();
	void destroyEntity(uint32_t id);

private:
	entt::registry m_registry;
};
