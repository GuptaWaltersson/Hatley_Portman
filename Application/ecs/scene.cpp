#include "scene.hpp"
#include "components.hpp"
#include <iostream>

Scene::Scene(lua_State* L)
{

}

int Scene::GetEntityCount()
{
	return m_registry.view<entt::entity>().size();
}

int Scene::CreateEntity()
{
	return (int)m_registry.create();
}

bool Scene::IsEntity(int entity)
{
	return m_registry.valid((entt::entity)entity);
}

void Scene::RemoveEntity(int entity)
{
	m_registry.destroy((entt::entity)entity);
}

void Scene::lua_openScene(lua_State* L, Scene* scene)
{
	lua_newtable(L);

	luaL_Reg methods[] = {
		{ "CreateEntity", lua_CreateEntity },
		{ "SetComponent", lua_SetComponent },
		{ NULL, NULL }
	};

	lua_pushlightuserdata(L, scene);
	luaL_setfuncs(L, methods, 1);
	lua_setglobal(L, "scene");
}

void Scene::UpdateSystems(float delta)
{
	for (auto it = m_system.begin(); it != m_system.end(); it++)
	{
		if ((*it)->OnUpdate(m_registry, delta))
		{
			delete(*it);
			it = m_system.erase(it);
		}

	}
}

Scene Scene::lua_GetSceneUpValue(lua_State* L)
{
	return 0;
}

int Scene::lua_CreateEntity(lua_State* L)
{
	Scene* scene = static_cast<Scene*>(lua_touserdata(L, lua_upvalueindex(1)));
	int entity = scene->CreateEntity();
	lua_pushinteger(L, entity);
	return 0;
}


int Scene::lua_SetComponent(lua_State* L) 
{
	Scene* scene = static_cast<Scene*>(lua_touserdata(L, lua_upvalueindex(1)));
	int entity = lua_tointeger(L, 1);

	lua_getfield(L, 3, "value");
	float value = luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	scene->SetComponent<Health>(entity, value);

	return 0;
}
