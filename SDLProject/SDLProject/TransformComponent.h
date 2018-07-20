#pragma once
#include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component
{

public:
	Vector2D m_oPosition;
	Vector2D m_oVelocity;

	int m_iSpeed;

	TransformComponent(int speed = 0)
	{
		m_oPosition.x = 0;
		m_oPosition.y = 0;
		m_iSpeed = speed;
	}

	TransformComponent(float x, float y, int speed = 0)
	{
		m_oPosition.x = x;
		m_oPosition.y = y;
		m_iSpeed = speed;
	}

	TransformComponent(const Vector2D& vec, int speed = 0)
	{
		m_oPosition = vec;
		m_iSpeed = speed;
	}

	void Init() override
	{
		m_oPosition.x = 0;
		m_oPosition.y = 0;

		m_oVelocity.x = 0;
		m_oVelocity.y = 0;
	}

	void Update() override
	{
		m_oPosition.x += m_oVelocity.x * m_iSpeed;
		m_oPosition.y += m_oVelocity.y * m_iSpeed;
	}
	void SetPos(float x, float y)
	{
		m_oPosition.x = x;
		m_oPosition.y = y;
	}
};