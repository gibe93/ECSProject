#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
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
	void Update()
	{
		std::for_each(m_vComponents.begin(), m_vComponents.end(), [](const unique_ptr<Component>& c) {c->Update(); });
	}
	void Draw() 
	{
		std::for_each(m_vComponents.begin(), m_vComponents.end(), [](const unique_ptr<Component>& c) {c->Draw(); });
	}
	bool IsActive() const { return m_bIsActive; }
	void Destroy() { m_bIsActive = false; }

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
	bool m_bIsActive = true;
	std::vector<std::unique_ptr<Component>> m_vComponents;

	ComponentArray m_aComponentsArray;
	ComponentBitSet m_oComponentBitSet;
};

class Manager 
{
private:
	std::vector<std::unique_ptr<Entity>> m_vEntities;

public:
	void Update()
	{
		std::for_each(m_vEntities.begin(), m_vEntities.end(), [](const std::unique_ptr<Entity>& e) { e->Update(); });
	}
	void Draw()
	{
		std::for_each(m_vEntities.begin(), m_vEntities.end(), [](const std::unique_ptr<Entity>& e) { e->Draw(); });
	}
	void Refresh()
	{
		m_vEntities.erase(std::remove_if(m_vEntities.begin(), m_vEntities.end(), [](const std::unique_ptr<Entity>& e) 
		{
			return !e->IsActive();
		}),
			std::end(m_vEntities));
	}

	Entity& AddEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		m_vEntities.emplace_back(std::move(uPtr));
		return *e;
	}
};
