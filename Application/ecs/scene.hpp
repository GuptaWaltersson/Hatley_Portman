#include "registry.hpp"
#include "lua.hpp"
#include "systems.hpp"



class Scene
{
	entt::registry m_registry;
	std::vector<System*> m_system;

public:
	Scene(lua_State* L);
	~Scene() = default;

	int GetEntityCount();
	int CreateEntity();
	bool IsEntity(int entity);
	void RemoveEntity(int entity);

	static void lua_openScene(lua_State* L, Scene* scene);

	void UpdateSystems(float delta);

public:
	template <typename... Args>
	bool HasComponents(int entity);

	template <typename T>
	T& GetComponent(int entity);

	template <typename T>
	void SetComponent(int entity, const T& component);

	template <typename T, typename... Args>
	void SetComponent(int entity, Args... args);

	template <typename T>
	void RemoveComponent(int entity);

	template < typename T, typename ... Args>
	void CreateSystem(Args ... args);
	
private:
	static Scene* lua_GetSceneUpValue(lua_State* L);

	static int lua_GetEntityCount(lua_State* L);
	static int lua_CreateEntity(lua_State* L);
	static int lua_IsEntity(lua_State* L);
	static int lua_RemoveEntity(lua_State* L);

	static int lua_HasComponent(lua_State* L);
	static int lua_GetComponent(lua_State* L);
	static int lua_SetComponent(lua_State* L);
	static int lua_RemoveComponent(lua_State* L);

};


template <typename... Args>
bool Scene::HasComponents(int entity) {
	return m_registry.all_of<Args...>((entt::entity)entity);
}

template <typename T>
T& Scene::GetComponent(int entity) {
	return m_registry.get<T>((entt::entity)entity);
}

template <typename T>
void Scene::SetComponent(int entity, const T& component) {
	m_registry.emplace_or_replace<T>((entt::entity)entity, component);
}

template <typename T, typename... Args>
void Scene::SetComponent(int entity, Args... args) {
	m_registry.emplace_or_replace<T>((entt::entity)entity, args...);
}

template <typename T>
void Scene::RemoveComponent(int entity) {
	m_registry.remove<T>((entt::entity)entity);
}

template < typename T, typename ... Args>
void Scene::CreateSystem(Args ... args)
{
	m_system.emplace_back(new T(args ...));
}