#include "playerScriptingBridge.h"
#include "player.h"
#include "lua.hpp"

static player* g_player = nullptr;
namespace playerScriptingBridge {
	void bind(lua_State* L, player* player)
	{
		g_player = player;

		lua_register(L, "setPlayerSpeed", [](lua_State* L) ->int {
			float speed = luaL_checknumber(L, 1);
			g_player->m_movementSpeed = speed;
			return 0;
			});


		lua_register(L, "getPlayerSpeed", [](lua_State* L)->int {
			lua_pushnumber(L, g_player->m_movementSpeed);
			return 1;
			});

	}
}

