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

			sceneJson.push_back(e);
		});


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

	std::ofstream out("scene.json");
	out << sceneJson.dump(4);
	std::cout << "Scene saved to scene.json" << std::endl;
}

void SceneManager::Load()
{

}
