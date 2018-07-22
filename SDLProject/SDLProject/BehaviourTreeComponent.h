#pragma once
#include "Components.h"
#include <string>
#include <memory.h>

class Node;

class BehaviourTreeComponent: public Component
{
private:
	Node* m_pRunningNode;

public:
	
	BehaviourTreeComponent(Node* startingNode)
	{
		m_pRunningNode = startingNode;
	}
	
	void Init() override
	{

	}

	void Update() override;

};
