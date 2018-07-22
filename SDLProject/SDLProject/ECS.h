#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Entity* entity;

	virtual void Init() {}
	virtual void Update() {}
	virtual void Draw() {}

	virtual ~Component() {}
};

class Entity
{
public:
	Entity(Manager& m) : manager(m){}

	void Update()
	{
		for (auto& c : m_vComponents) c->Update();
	}
	void Draw() 
	{
		for (auto& c : m_vComponents) c->Draw();
	}
	bool IsActive() const { return m_bIsActive; }
	void Destroy() { m_bIsActive = false; }

	bool HasGroup(Group mGroup)
	{
		return m_oGroupBitSet[mGroup];
	}

	void AddGroup(Group mGroup);

	void DeleteGroup(Group mGroup)
	{
		m_oGroupBitSet[mGroup] = false;
	}

	template<typename T> bool HasComponent() const 
	{
		return m_oComponentBitSet[getComponentTypeID<T>()];
	}

	template<typename T, typename... TArgs>
	T& AddComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		m_vComponents.emplace_back(std::move(uPtr));

		m_aComponentsArray[getComponentTypeID<T>()] = c;
		m_oComponentBitSet[getComponentTypeID<T>()] = true;

		c->Init();
		return *c;
	}

	template<typename T> T& GetComponent() const 
	{
		auto ptr(m_aComponentsArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

private:
	Manager& manager;
	bool m_bIsActive = true;
	std::vector<std::unique_ptr<Component>> m_vComponents;

	ComponentArray m_aComponentsArray;
	ComponentBitSet m_oComponentBitSet;
	GroupBitSet m_oGroupBitSet;
};

class Manager 
{
private:
	std::vector<std::unique_ptr<Entity>> m_vEntities;
	std::array<std::vector<Entity*>, maxGroups> m_aGroupedEntites;

public:
	void Update()
	{
		for (auto& e : m_vEntities) e->Update();
	}
	void Draw()
	{
		for (auto& e : m_vEntities) e->Draw();
	}
	void Refresh()
	{
		for(auto i(0u); i<maxGroups; i++)
		{
			auto& v(m_aGroupedEntites[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v), [i](Entity* mEntity) {
				return !mEntity->IsActive() || !mEntity->HasGroup(i);
			}),
				std::end(v));
		}

		m_vEntities.erase(std::remove_if(m_vEntities.begin(), m_vEntities.end(), [](const std::unique_ptr<Entity>& e) 
		{
			return !e->IsActive();
		}),
			std::end(m_vEntities));
	}

	void AddToGroup(Entity* mEntity, Group mGroup)
	{
		m_aGroupedEntites[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& GetGroup(Group mGroup)
	{
		return m_aGroupedEntites[mGroup];
	}

	Entity& AddEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		m_vEntities.emplace_back(std::move(uPtr));
		return *e;
	}
};
