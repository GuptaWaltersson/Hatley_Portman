#include "sceneManager.hpp"
#include "json.hpp"
#include <fstream>
#include <iostream>

void SceneManager::Save()
{
	using json = nlohmann::json;

	json sceneJson = json::array();

	auto view = m_registry.view<Tag>();
	for (auto entity : view)
	{
		json entityJson;

		if (m_registry.all_of<Position>(entity))
			entityJson["position"] = { {"x", m_registry.get<Position>(entity).x}, {"y", m_registry.get<Position>(entity).y} };

		if (m_registry.all_of<BBox>(entity))
			entityJson["bbox"] = { {"width", m_registry.get<BBox>(entity).width}, {"height", m_registry.get<BBox>(entity).height} };

		if (m_registry.all_of<Movement>(entity))
			entityJson["movement"] = { {"dx", m_registry.get<Movement>(entity).dx}, {"dy", m_registry.get<Movement>(entity).dy}, {"ax", m_registry.get<Movement>(entity).ax}, {"ay", m_registry.get<Movement>(entity).ay}, {"canJump", m_registry.get<Movement>(entity).canJump} };

		if (m_registry.all_of<Gravity>(entity))
			entityJson["gravity"] = { {"acceleration", m_registry.get<Gravity>(entity).acceleration} };

		if (m_registry.all_of<PlayerTag>(entity))
			entityJson["playertag"] = m_registry.get<PlayerTag>(entity).isPlayer;

		if (m_registry.all_of<HatTag>(entity))
			entityJson["hattag"] = { {"onHead", m_registry.get<HatTag>(entity).onHead}, { "hatType", m_registry.get<HatTag>(entity).hatType} };
				 
		if (m_registry.all_of<LastMove>(entity))
			entityJson["lastmove"] = m_registry.get<LastMove>(entity).lastKey;

		if (m_registry.all_of<GroupID>(entity))
			entityJson["group"] = m_registry.get<GroupID>(entity).id;

		sceneJson.push_back(entityJson);
		std::cout << "Scene saved to scene.json" << std::endl;
	}
}

void SceneManager::Load()
{

}
