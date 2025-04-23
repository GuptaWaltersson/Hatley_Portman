#include "registry.hpp"

ECSRegistry& ECSRegistry::instance()
{
	static ECSRegistry instance;
    return instance;
}

entt::registry& ECSRegistry::getRegistry()
{
	return m_registry;
}

uint32_t ECSRegistry::createEntity()
{
    auto entity = m_registry.create();
	return static_cast<uint32_t>(entity);
}

void ECSRegistry::destroyEntity(uint32_t id)
{
	m_registry.destroy(static_cast<entt::entity>(id));
}
