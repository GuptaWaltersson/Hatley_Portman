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
	using json = nlohmann::json;

	std::ifstream file("scene.json");
	if (!file.is_open())
	{
		std::cerr << "Failed to open scene.json" << std::endl;
		return;
	}

	json sceneJson;
	file >> sceneJson;

	m_registry.clear();

	for (auto& entityJson : sceneJson)
	{
		auto entity = m_registry.create();

		if (entityJson.contains("tag"))
			m_registry.emplace<Tag>(entity, entityJson["tag"].get<std::string>());

		if (entityJson.contains("sprite") && entityJson["sprite"].is_object())
		{
			auto& spriteData = entityJson["sprite"];
			std::string texturePath = spriteData.at("texturePath").get<std::string>();
			int scale = spriteData.at("scale").get<int>();

			auto& sprite = m_registry.emplace<Sprite>(entity, texturePath);
			sprite.scale = scale;
		}

		if (entityJson.contains("position"))
		{
			auto& posData = entityJson["position"];
			m_registry.emplace<Position>(entity, posData["x"].get<float>(), posData["y"].get<float>());
		}

		if (entityJson.contains("bbox"))
		{
			auto& bboxData = entityJson["bbox"];
			m_registry.emplace<BBox>(entity, bboxData["width"].get<float>(), bboxData["height"].get<float>());
		}

		if (entityJson.contains("movement"))
		{
			auto& moveData = entityJson["movement"];
			m_registry.emplace<Movement>(entity, moveData["dx"].get<float>(), moveData["dy"].get<float>(), moveData["ax"].get<float>(), moveData["ay"].get<float>(), moveData["canJump"].get<bool>());
		}

		if (entityJson.contains("gravity"))
			m_registry.emplace<Gravity>(entity, entityJson["gravity"]["acceleration"].get<float>());

		if (entityJson.contains("playertag"))
			m_registry.emplace<PlayerTag>(entity, entityJson["playertag"].get<bool>());

		if (entityJson.contains("hattag"))
			m_registry.emplace<HatTag>(entity, entityJson["hattag"]["onHead"].get<bool>(), entityJson["hattag"]["hatType"].get<int>());

		if (entityJson.contains("lastmove"))
			m_registry.emplace<LastMove>(entity, entityJson["lastmove"].get<std::string>());

		if (entityJson.contains("group"))
			m_registry.emplace<GroupID>(entity, entityJson["group"].get<int>());
	}
	std::cout << "Scene loaded from scene.json" << std::endl;
}
