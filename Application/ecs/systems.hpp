#pragma once

#include "lua.hpp"
#include "entt.hpp"
#include "components.hpp"

class System
{
public:
	virtual bool OnUpdate(entt::registry& registry, float delta) = 0;
};

class PoisonSystem : public System {
	int m_lifetime;

public:
	PoisonSystem(int lifetime) : m_lifetime(lifetime) {}

	bool OnUpdate(entt::registry& registry, float delta) final {
		auto view = registry.view<Health, Poison>();
		view.each([](Health& health, const Poison& poison) {
			health.value -= poison.tickDamage;
			});

		return (--m_lifetime) <= 0;
	}
};

class CleanupSystem : public System {
public:
	bool OnUpdate(entt::registry& registry, float delta) final {
		auto view = registry.view<Health>();
		view.each([&](entt::entity entity, const Health& health) {
			if (health.value <= 0.f) {
				registry.destroy(entity);
			}
			});
		return false;
	}
};

class InfoSystem : public System {
	int m_updateCounter = 0;

public:
	InfoSystem() = default;

	bool OnUpdate(entt::registry& registry, float delta) final {
		int count = registry.view<entt::entity>().size();
		auto healthView = registry.view<Health>();
		auto poisonView = registry.view<Poison>();
		printf("\n-- Update %i --\n", ++m_updateCounter);
		printf("Living entities:\t%i\n", static_cast<int>(healthView.size()));
		printf("Poisoned entities:\t%i\n", static_cast<int>(poisonView.size()));

		return false;
	}
};
