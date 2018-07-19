#pragma once
#include "Components.h"

class PositionComponent : public Component
{
private:
	int m_iXpos;
	int m_iYpos;

public:
	int X() { return m_iXpos; }
	int Y() { return m_iYpos; }

	PositionComponent()
	{
		m_iXpos = 0;
		m_iYpos = 0;
	}

	PositionComponent(int x, int y)
	{
		m_iXpos = x;
		m_iYpos = y;
	}

	void Init() override
	{
		m_iYpos = 0;
		m_iXpos = 0;
	}

	void Update() override
	{

	}
	void SetPos(int x, int y)
	{
		m_iYpos = y;
		m_iXpos = x;
	}
};