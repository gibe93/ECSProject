#pragma once
#include "Components.h"
#include <string>
#include <memory.h>

class State;

class BehaviourTreeComponent: public Component
{
private:
	State* m_pRunningNode;

public:
	
	BehaviourTreeComponent(State* startingNode)
	{
		m_pRunningNode = startingNode;
	}
	
	void Init() override
	{

	}

	void Update() override;

};
