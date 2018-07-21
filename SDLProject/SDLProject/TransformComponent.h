#pragma once
#include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component
{

public:
	Vector2D m_oPosition;
	Vector2D m_oVelocity;

	bool m_bIsMoving = false;

	int m_iScale = 1;
	int m_iSpeed = 0;

	int m_iHeight = 32;
	int m_iWidth = 32;

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

	TransformComponent(float x, float y, int width, int height, int scale, int speed = 0)
	{
		m_oPosition.x = x;
		m_oPosition.y = y;
		m_iScale = scale;
		m_iSpeed = speed;
		m_iWidth = width;
		m_iHeight = height;
		m_iSpeed = speed;
	}

	TransformComponent(const Vector2D& vec, int scale = 1, int speed = 0)
	{
		m_oPosition = vec;
		m_iScale = scale;
		m_iSpeed = speed;
	}

	void Init() override
	{
		m_oVelocity.x = 0;
		m_oVelocity.y = 0;
	}

	void Update() override
	{
		m_oPosition.x += m_oVelocity.x * m_iSpeed;
		m_oPosition.y += m_oVelocity.y * m_iSpeed;
		if(m_oVelocity!=0)
		{
			m_bIsMoving = true;
		}
		else m_bIsMoving = false;
	}
	void SetPos(float x, float y)
	{
		m_oPosition.x = x;
		m_oPosition.y = y;
	}
};