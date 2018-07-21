#pragma once

struct Animation
{
	int m_iIndex;
	int m_iFrames;
	int m_iSpeed;

	Animation(){}
	Animation(int i, int f, int s)
	{
		m_iIndex = i;
		m_iFrames = f;
		m_iSpeed = s;
	}
};