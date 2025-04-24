#include <iostream>

#include "scene.hpp"
#include "components.hpp"
#include <string>


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
		{ "GetComponent", lua_GetComponent },
		{ "RemoveComponent", lua_RemoveComponent },
		{ "HasComponent", lua_HasComponent },
		{ "IsEntity", lua_IsEntity },
		{ "GetEntityCount", lua_GetEntityCount },
		{ "RemoveEntity", lua_RemoveEntity },
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

Scene* Scene::lua_GetSceneUpValue(lua_State* L)
{
	Scene* scene = nullptr;
	if (lua_isuserdata(L, lua_upvalueindex(1)))
	{
		scene = static_cast<Scene*>(lua_touserdata(L, lua_upvalueindex(1)));
	}
	return scene;
}

int Scene::RefAndPushBehaviour(lua_State* L, int entity, const char* path) 
{
	luaL_dofile(L, path);

	lua_pushvalue(L, -1);
	int luaTableRef = luaL_ref(L, LUA_REGISTRYINDEX);

	lua_pushinteger(L, entity);
	lua_setfield(L, -2, "ID");

	lua_pushstring(L, path);
	lua_setfield(L, -2, "path");

	lua_getfield(L, -1, "OnCreate");
	lua_pushvalue(L, -2);
	lua_pcall(L, 1, 0, 0);

	return luaTableRef;
}

int Scene::lua_GetEntityCount(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int count = scene->GetEntityCount();
	lua_pushinteger(L, count);
	return 1;
}

int Scene::lua_CreateEntity(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int entity = scene->CreateEntity();
	lua_pushinteger(L, entity);
	return 1;
}

int Scene::lua_IsEntity(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int entity = lua_tointeger(L, 1);
	bool alive = scene->IsEntity(entity);
	lua_pushboolean(L, alive);
	return 1;
}

int Scene::lua_RemoveEntity(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int entity = lua_tointeger(L, 1);
	scene->RemoveEntity(entity);
	return 0;
}

int Scene::lua_HasComponent(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int entity = lua_tointeger(L, 1);
	std::string type = lua_tostring(L, 2);

	bool hasComponent = false;

	if (type == "sprite") {
		hasComponent = scene->HasComponents<Sprite>(entity);
	}
	else if (type == "behaviour") {
		hasComponent = scene->HasComponents<Behaviour>(entity);
	}
	else
	if (type == "health") {
		hasComponent = scene->HasComponents<Health>(entity);
	}
	else if (type == "poison") {
		hasComponent = scene->HasComponents<Poison>(entity);
	}
	else if (type == "gravity") {
		hasComponent = scene->HasComponents<Gravity>(entity);
	}
	lua_pushboolean(L, hasComponent);
	return 1;
}

int Scene::lua_GetComponent(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int entity = lua_tointeger(L, 1);
	std::string type = lua_tostring(L, 2);
	
	if (type == "sprite" && scene->HasComponents<Sprite>(entity))
	{
		Sprite& sprite = scene->GetComponent<Sprite>(entity);
		std::string textureId = std::to_string(sprite.texture.id);
		lua_pushstring(L, textureId.c_str());
	}
	else if (type == "health" && scene->HasComponents<Health>(entity))
	{
		Health& health = scene->GetComponent<Health>(entity);
		lua_pushnumber(L, health.value);
	}
	else if (type == "poison" && scene->HasComponents<Poison>(entity))
	{
		Poison& poison = scene->GetComponent<Poison>(entity);
		lua_pushnumber(L, poison.tickDamage);
	}
	else if (type == "gravity" && scene->HasComponents<Gravity>(entity))
	{
		Gravity& grav = scene->GetComponent<Gravity>(entity);
		lua_pushnumber(L, grav.acceleration);
	}
	return 1;
}

int Scene::lua_SetComponent(lua_State* L) 
{
	Scene* scene = static_cast<Scene*>(lua_touserdata(L, lua_upvalueindex(1)));
	int entity = lua_tointeger(L, 1);
	std::string type = lua_tostring(L, 2);

	if (type == "sprite")
	{
		std::string path = lua_tostring(L, 3);
		scene->SetComponent<Sprite>(entity, path.c_str());
	}
	if (type == "health")
	{
		float value = lua_tonumber(L, 3);
		scene->SetComponent<Health>(entity, value);
	}
	else if (type == "poison")
	{
		float value = lua_tonumber(L, 3);
		scene->SetComponent<Poison>(entity, value);
	}
	else if (type == "gravity")
	{
		float value = lua_tonumber(L, 3);
		scene->SetComponent<Gravity>(entity, value);
	}
	else if (type == "behaviour")
	{
		if (scene->HasComponents<Behaviour>(entity))
		{
			scene->RemoveComponent<Behaviour>(entity);
		}

		const char* path = lua_tostring(L, 3);
		int ref = RefAndPushBehaviour(L, entity, path);
		scene->SetComponent<Behaviour>(entity, Behaviour(path, ref));
		return 1;
	}

	return 0;
}

int Scene::lua_RemoveComponent(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int entity = lua_tointeger(L, 1);
	std::string type = lua_tostring(L, 2);

	if (type == "sprite")
	{
		scene->RemoveComponent<Sprite>(entity);
	}
	else if (type == "behaviour")
	{
		scene->RemoveComponent<Behaviour>(entity);
	}
	else
	if (type == "health")
	{
		scene->RemoveComponent<Health>(entity);
	}
	else if (type == "poison")
	{
		scene->RemoveComponent<Poison>(entity);
	}
	else if (type == "gravity")
	{
		scene->RemoveComponent<Gravity>(entity);
	}
	return 0;
}
