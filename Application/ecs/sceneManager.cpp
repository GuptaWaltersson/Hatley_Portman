#include "sceneManager.hpp"
#include "json.hpp"
#include <fstream>
#include <iostream>

void SceneManager::Save()
{
	using json = nlohmann::json;
	json sceneJson = json::array();

	auto viewPlayer = m_registry.view<Tag, Sprite, Position, BBox, Movement, Gravity, PlayerTag, LastMove>();
	viewPlayer.each([&](Tag& tag, Sprite& sprite, Position& pos, BBox& box, Movement& movement, Gravity& gravity, PlayerTag& playertag, LastMove& lastmove)
		{
			json e;
			e["tag"] = tag.name;
			e["sprite"] = sprite.texturePath;
			e["position"] = { {"x", pos.x}, {"y", pos.y} };
			e["bbox"] = { {"width", box.width}, {"height", box.height} };
			e["movement"] = { {"dx", movement.dx}, {"dy", movement.dy}, {"ax", movement.ax}, {"ay", movement.ay}, {"canJump", movement.canJump} };
			e["gravity"] = { {"acceleration", gravity.acceleration} };
			e["playertag"] = playertag.isPlayer;
			e["lastmove"] = lastmove.lastKey;

<<<<<<< Updated upstream
			sceneJson.push_back(e);
		});
=======
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
>>>>>>> Stashed changes


	auto viewBlock = m_registry.view<Tag, Sprite, Position, BBox, GroupID>();
	viewBlock.each([&](Tag& tag, Sprite& sprite, Position& pos, BBox& box, GroupID& group)
		{
			json e;
			e["tag"] = tag.name;
			e["sprite"] = sprite.texturePath;
			e["position"] = { {"x", pos.x}, {"y", pos.y} };
			e["bbox"] = { {"width", box.width}, {"height", box.height} };
			e["group"] = group.id;

			sceneJson.push_back(e);
		});

	auto viewCoin = m_registry.view<Tag, Sprite, Position, BBox>();
	viewCoin.each([&](Tag& tag, Sprite& sprite, Position& pos, BBox& box)
		{
			if (tag.name == "coin")
			{
				json e;
				e["tag"] = tag.name;
				e["sprite"] = sprite.texturePath;
				e["position"] = { {"x", pos.x}, {"y", pos.y} };
				e["bbox"] = { {"width", box.width}, {"height", box.height} };

				sceneJson.push_back(e);
			}
		});

<<<<<<< Updated upstream
	std::ofstream out("scene.json");
	out << sceneJson.dump(4);
=======
		if (m_registry.all_of<GroupID>(entity))
			entityJson["group"] = m_registry.get<GroupID>(entity).id;

		sceneJson.push_back(entityJson);
	}
>>>>>>> Stashed changes
	std::cout << "Scene saved to scene.json" << std::endl;
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

		if(entityJson.contains("tag"))
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
