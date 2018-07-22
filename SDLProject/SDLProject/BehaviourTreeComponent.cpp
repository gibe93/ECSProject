#include "BehaviourTreeComponent.h"
#include "BehaviourTree.h"

void BehaviourTreeComponent::Update()
{
	m_pRunningNode->Run();
	m_pRunningNode = m_pRunningNode->CheckConditions();
}
