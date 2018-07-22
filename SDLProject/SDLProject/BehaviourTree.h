#pragma once
#include <vector>
#include <algorithm>
#include <memory>
#include <iostream>
#include "Components.h"
#include <functional>
#include "Vector2D.h"

using namespace std;

class Node
{
private:
	Node* m_pFather;
	std::vector<Node*> m_vChildren;
	string m_sNodeName;
	Entity* m_pOwner;

	virtual bool CheckEnterCondition() = 0;
	virtual Node* EnterNode() { return this; }
	virtual void ExitNode() {}


public:
	Entity* Owner()
	{
		return m_pOwner;
	}

	Node(Node* father, Entity* owner, string name)
	{
		m_pFather = father;
		m_pOwner = owner;
		m_sNodeName = name;
	}

	virtual void AddChild(Node* child)
	{
		m_vChildren.emplace_back(child);
	}

	virtual Node* CheckConditions()
	{
		for (Node* n : m_vChildren)
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

class RootNode : public Node
{
public:
	RootNode(Node* father, Entity* owner) : Node(father, owner, "NodeOne") {}

	bool CheckEnterCondition() override
	{
		return true;
	}
};


class MoveToNode : public Node
{
private:
	Vector2D m_oDestination;
	Entity* m_pDestinationEntity;
	float m_fAcceptableDistance;
	bool b_mFollowMousePos;

public:
	MoveToNode(Node* father, Entity* owner, float acceptableDistance) : Node(father, owner, "MoveTo")
	{
		m_oDestination = Vector2D(0, 0);
		m_fAcceptableDistance = acceptableDistance;
		m_pDestinationEntity = nullptr;
		b_mFollowMousePos = true;
	}

	MoveToNode(Node* father, Entity* owner, Vector2D Dest, float acceptableDistance, bool followMouse = false) : Node(father, owner, "MoveTo")
	{
		m_oDestination = Dest;
		m_fAcceptableDistance = acceptableDistance;
		m_pDestinationEntity = nullptr;
		b_mFollowMousePos = followMouse;
	}

	MoveToNode(Node* father, Entity* owner, float xDest, float yDest, float acceptableDistance, bool followMouse = false) : Node(father, owner, "MoveTo")
	{
		m_oDestination = Vector2D(xDest, yDest);
		m_fAcceptableDistance = acceptableDistance;
		m_pDestinationEntity = nullptr;
		b_mFollowMousePos = followMouse;

	}

	MoveToNode(Node* father, Entity* owner, Entity* other, float acceptableDistance, bool followMouse = false) : Node(father, owner, "MoveTo")
	{
		m_fAcceptableDistance = acceptableDistance;
		m_pDestinationEntity = other;
		m_oDestination = Vector2D(m_pDestinationEntity->GetComponent<TransformComponent>().m_oPosition);
		b_mFollowMousePos = followMouse;

	}

	bool CheckEnterCondition() override
	{
		if (b_mFollowMousePos)
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
		}

		if (Owner()->GetComponent<TransformComponent>().m_oPosition.Distance(m_oDestination) > m_fAcceptableDistance) return true;
		else return false;
	}

	void Run()override
	{
		Node::Run();
		if (b_mFollowMousePos)
		{
			int x;
			int y;
			SDL_GetMouseState(&x, &y);
			//cout << x << " - " << y << endl;
			m_oDestination.x = (float)x;
			m_oDestination.y = (float)y;
		}
		else if (m_pDestinationEntity != nullptr)
		{
			m_oDestination = m_pDestinationEntity->GetComponent<TransformComponent>().m_oPosition;
		}
		if (Owner()->GetComponent<TransformComponent>().m_oPosition.Distance(m_oDestination) <= m_fAcceptableDistance)
		{
			Owner()->GetComponent<TransformComponent>().m_oVelocity = Owner()->GetComponent<TransformComponent>().m_oVelocity.Zero();
		}
		else if (b_mFollowMousePos)
		{
			Vector2D direction;
			direction = (m_oDestination - Owner()->GetComponent<TransformComponent>().m_oPosition);
			direction.Normalize();
			Owner()->GetComponent<TransformComponent>().m_oVelocity = direction;
		}
		
	}

	Node* EnterNode() override
	{
		Vector2D direction;
		if (Owner()->GetComponent<TransformComponent>().m_oPosition.Distance(m_oDestination) > m_fAcceptableDistance)
		{
			direction = (m_oDestination - Owner()->GetComponent<TransformComponent>().m_oPosition);
			direction.Normalize();
			Owner()->GetComponent<TransformComponent>().m_oVelocity = direction;
		}
		/*cout << m_oDestination.x << " - " << m_oDestination.y << endl;
		cout << Owner()->GetComponent<TransformComponent>().m_oPosition.Distance(m_oDestination) << endl;
		cout << direction.x << " - " << direction.y << endl;*/
		return this;
	}
};