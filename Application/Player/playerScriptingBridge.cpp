#include "playerScriptingBridge.h"
#include "player.h"
#include "lua.hpp"

static player* g_player = nullptr;
namespace playerScriptingBridge {
	void bind(lua_State* L, player* player)
	{
		g_player = player;
		// definerar funktioner till lua filen där vi kan köra de
		lua_register(L, "setPlayerSpeed", [](lua_State* L) ->int {
			float speed = luaL_checknumber(L, 1);
			g_player->setSpeed(speed);
			return 0;
			});

		// get funktioner är väl lite sisådär onödiga för lua men men
		lua_register(L, "getPlayerSpeed", [](lua_State* L)->int {
			lua_pushnumber(L, g_player->getSpeed());
			return 1;
			});

		lua_register(L, "setPlayerTexture", [](lua_State* L)->int {
			std::string textureName = luaL_checkstring(L, 1);
			g_player->setTextureName(textureName);
			return 0;
			});

		lua_register(L, "getPLayerTexture", [](lua_State* L)-> int {
			lua_pushstring(L, g_player->getTextureName().c_str());
			return 1;
			});

	}
}

