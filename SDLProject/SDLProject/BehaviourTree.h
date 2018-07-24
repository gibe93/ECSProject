#pragma once
#include <vector>
#include <algorithm>
#include <memory>
#include <iostream>
#include "Components.h"
#include <functional>
#include "Vector2D.h"
#include "AStar.h"
#include "TileMap.h"

using namespace std;

class State
{
private:
	State* m_pFather;
	std::vector<State*> m_vChildren;
	string m_sNodeName;
	Entity* m_pOwner;


	virtual bool CheckEnterCondition() = 0;
	virtual State* EnterNode() { return this; }
	virtual void ExitNode() {}

public:



	Entity* Owner()
	{
		return m_pOwner;
	}

	State(State* father, Entity* owner, string name)
	{
		m_pFather = father;
		m_pOwner = owner;
		m_sNodeName = name;
	}

	virtual void AddChild(State* child)
	{
		m_vChildren.emplace_back(child);
	}

	virtual State* CheckConditions()
	{
		for (State* n : m_vChildren)
		{
			if (n->CheckEnterCondition())
			{
				this->ExitNode();
				return n->EnterNode();
			}
		}
		if (CheckEnterCondition()) return this;
		else
		{
			if (m_pFather != nullptr)
			{
				this->ExitNode();
				return m_pFather->EnterNode();
			}
			else return this;
		}
	}

	virtual void Run()
	{
		cout << m_sNodeName << endl;
	}



};

class RootNode : public State
{
public:
	RootNode(State* father, Entity* owner) : State(father, owner, "NodeOne") {}

	bool CheckEnterCondition() override
	{
		return true;
	}
};


class MoveToNode : public State
{
private:
	Vector2D m_oDestination;
	Entity* m_pDestinationEntity;
	float m_fAcceptableDistance;
	bool b_mFollowMousePos;
	TileMap* m_pMap;
	std::vector<Coord> m_vWayPoints;
	int i;
	Vector2D nextPoint;

public:
	/*MoveToNode(State* father, Entity* owner, TileMap* map, float acceptableDistance) : State(father, owner, "MoveTo")
	{
		m_oDestination = Vector2D(0, 0);
		m_fAcceptableDistance = acceptableDistance;
		m_pDestinationEntity = nullptr;
		b_mFollowMousePos = true;
		m_pMap = map;
	}*/

	MoveToNode(State* father, Entity* owner, TileMap* map, Vector2D Dest, float acceptableDistance, bool followMouse = false) : State(father, owner, "MoveTo")
	{
		m_oDestination = Dest;
		m_fAcceptableDistance = acceptableDistance;
		m_pDestinationEntity = nullptr;
		b_mFollowMousePos = followMouse;
		m_pMap = map;
		nextPoint = Vector2D(0, 0);
	}

	MoveToNode(State* father, Entity* owner, TileMap* map, float xDest, float yDest, float acceptableDistance, bool followMouse = false) : State(father, owner, "MoveTo")
	{
		m_oDestination = Vector2D(xDest, yDest);
		m_fAcceptableDistance = acceptableDistance;
		m_pDestinationEntity = nullptr;
		b_mFollowMousePos = followMouse;
		m_pMap = map;
		nextPoint = Vector2D(0, 0);
	}

	/*MoveToNode(State* father, Entity* owner, TileMap* map, Entity* other, float acceptableDistance, bool followMouse = false) : State(father, owner, "MoveTo")
	{
		m_fAcceptableDistance = acceptableDistance;
		m_pDestinationEntity = other;
		m_oDestination = Vector2D(m_pDestinationEntity->GetComponent<TransformComponent>().m_oPosition);
		b_mFollowMousePos = followMouse;
		m_pMap = map;
	}*/

	bool CheckEnterCondition() override
	{
		/*	if (b_mFollowMousePos)
			{
				int x;
				int y;
				SDL_GetMouseState(&x, &y);
				m_oDestination.x = (float)x;
				m_oDestination.y = (float)y;
			}
			else if (m_pDestinationEntity != nullptr)
			{
				m_oDestination = m_pDestinationEntity->GetComponent<TransformComponent>().m_oPosition;
			}*/

		if (Owner()->GetComponent<TransformComponent>().m_oPosition.Distance(m_oDestination) > m_fAcceptableDistance) return true;
		else return false;
	}

	void Run()override
	{
		State::Run();
		//if (b_mFollowMousePos)
		//{
		//	int x;
		//	int y;
		//	SDL_GetMouseState(&x, &y);
		//	//cout << x << " - " << y << endl;
		//	m_oDestination.x = (float)x;
		//	m_oDestination.y = (float)y;
		//}
		//else if (m_pDestinationEntity != nullptr)
		//{
		//	m_oDestination = m_pDestinationEntity->GetComponent<TransformComponent>().m_oPosition;
		//}
		//
		nextPoint.x = (int)(m_vWayPoints.at(i).x) * 32;
		nextPoint.y = (int)(m_vWayPoints.at(i).y) * 32;
		
		Vector2D direction(0.0f, 0.0f);
		if (Owner()->GetComponent<TransformComponent>().m_oPosition.Distance(m_oDestination) > m_fAcceptableDistance)
		{
			float p = nextPoint.x - Owner()->GetComponent<TransformComponent>().m_oPosition.x;
			float l = nextPoint.y - Owner()->GetComponent<TransformComponent>().m_oPosition.y;
			direction.x = p;
			direction.y = l;
			direction.Normalize();
			Owner()->GetComponent<TransformComponent>().m_oVelocity = direction;
		}
		/*else if (b_mFollowMousePos)
		{

			direction = (m_oDestination - Owner()->GetComponent<TransformComponent>().m_oPosition);
			direction.Normalize();
			Owner()->GetComponent<TransformComponent>().m_oVelocity = direction;
		}*/
	
		if (nextPoint.Distance(Owner()->GetComponent<TransformComponent>().m_oPosition) <= m_fAcceptableDistance)
		{
			Owner()->GetComponent<TransformComponent>().m_oVelocity = Owner()->GetComponent<TransformComponent>().m_oVelocity.Zero();
			i++;
		}
		//m_vWayPoints.clear();
	}

	State* EnterNode() override
	{
		i = 0;
		int j = (int)Owner()->GetComponent<TransformComponent>().m_oPosition.x / 32;
		int k = (int)Owner()->GetComponent<TransformComponent>().m_oPosition.y / 32;
		m_vWayPoints = m_pMap->m_pAStarGenerator->findPath({ j, k }, { (int)m_oDestination.x / 32, (int)m_oDestination.y / 32 });
		std::reverse(m_vWayPoints.begin(), m_vWayPoints.end());
		/*Vector2D direction;
		if (Owner()->GetComponent<TransformComponent>().m_oPosition.Distance(m_oDestination) > m_fAcceptableDistance)
		{
			direction = (m_oDestination - Owner()->GetComponent<TransformComponent>().m_oPosition);
			direction.Normalize();
			Owner()->GetComponent<TransformComponent>().m_oVelocity = direction;
		}*/
		/*cout << m_oDestination.x << " - " << m_oDestination.y << endl;
		cout << Owner()->GetComponent<TransformComponent>().m_oPosition.Distance(m_oDestination) << endl;
		cout << direction.x << " - " << direction.y << endl;*/
		return this;
	}
};