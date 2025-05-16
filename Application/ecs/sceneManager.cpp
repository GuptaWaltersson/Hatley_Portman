#include "sceneManager.hpp"
#include "editSystem.hpp"
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <set>
#include <optional>

void SceneManager::Save()
{
	using json = nlohmann::json;

	json sceneJson = json::array();

	auto view = m_registry.view<Tag>();
	for (auto entity : view)
	{
		json entityJson;

		if (m_registry.get<Tag>(entity).name == "ground1" || m_registry.get<Tag>(entity).name == "ground2")
			continue;

		if (m_registry.all_of<Tag>(entity))
			entityJson["tag"] = m_registry.get<Tag>(entity).name;

		if (m_registry.all_of<Sprite>(entity))
		{
			const auto& sprite = m_registry.get<Sprite>(entity);
			entityJson["sprite"] = {
				{"texturePath", sprite.texturePath},
				{"scale", sprite.scale}
			};
		}

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

		if (m_registry.all_of<Behaviour>(entity))
		{
			const auto& behaviour = m_registry.get<Behaviour>(entity);
			entityJson["behaviour"] = behaviour.ScriptPath;
		}

		sceneJson.push_back(entityJson);
	}
	std::ofstream file("scene.json");
	file << sceneJson.dump(4);
	file.close();

	std::cout << "Scene saved to scene.json" << std::endl;
}

void SceneManager::Load()
{
	using json = nlohmann::json;
	EditingSystem edit(m_L, m_registry);

	std::ifstream file("scene.json");
	if (!file.is_open())
	{
		std::cerr << "Failed to open scene.json" << std::endl;
		return;
	}

	json sceneJson;
	file >> sceneJson;

	std::map<std::pair<std::string, std::optional<int>>, json> bestEntities;

	for (auto& entityJson : sceneJson)
	{
		if (!entityJson.contains("tag") || !entityJson.contains("position"))
			continue;

		std::string tag = entityJson["tag"].get<std::string>();
		auto pos = entityJson["position"];
		float x = pos["x"].get<float>();
		float y = pos["y"].get<float>();

		std::optional<int> groupId = std::nullopt;
		if (entityJson.contains("group"))
			groupId = entityJson["group"].get<int>();

		auto key = std::make_pair(tag, groupId);

		// Compare and keep entity closest to top-left (smallest y, then smallest x)
		if (!bestEntities.count(key)) {
			bestEntities[key] = entityJson;
		}
		else {
			auto& current = bestEntities[key];
			float cx = current["position"]["x"].get<float>();
			float cy = current["position"]["y"].get<float>();

			if (y < cy || (y == cy && x < cx)) {
				bestEntities[key] = entityJson;
			}
		}
	}

	for (const auto& [key, entityJson] : bestEntities)
	{
		if (entityJson.contains("tag"))
		{
			const std::string& tag = key.first;


			if (tag == "cloud")
			{
				float x = entityJson["position"]["x"].get<float>();
				float y = entityJson["position"]["y"].get<float>();
				//int width = entityJson["bbox"]["width"].get<float>();
				edit.CreateCloud(x, y, 4);
			}
			else if (tag == "tree")
			{
				float x = entityJson["position"]["x"].get<float>();
				float y = entityJson["position"]["y"].get<float>();
				//int width = entityJson["bbox"]["width"].get<float>();
				//int height = entityJson["bbox"]["height"].get<float>();
				edit.CreateTree(x, y, 2, 2);
			}
			else if (tag == "coin")
			{
				float x = entityJson["position"]["x"].get<float>();
				float y = entityJson["position"]["y"].get<float>();
				edit.CreateCoin(x, y);
			}
			else if (tag == "mushroom")
			{
				float x = entityJson["position"]["x"].get<float>();
				float y = entityJson["position"]["y"].get<float>();
				//int width = entityJson["bbox"]["width"].get<float>();
				edit.CreateBigMushroom(x, y, 5);
			}
		}
	}
	std::cout << "Scene loaded from scene.json" << std::endl;
}
