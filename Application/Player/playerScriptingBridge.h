#pragma once

struct lua_State;
class player;

namespace playerScriptingBridge {
    void bind(lua_State* L, player* player);
}

