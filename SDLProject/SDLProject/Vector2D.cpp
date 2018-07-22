#include "Vector2D.h"
#include <math.h>

Vector2D::Vector2D()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2D & Vector2D::Add(const Vector2D & vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return *this;
}

Vector2D& Vector2D::Subtract(const Vector2D& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return *this;
}

Vector2D & Vector2D::Multiply(const Vector2D & vec)
{
	this->x *= vec.x;
	this->y *= vec.y;
	return *this;
}

Vector2D & Vector2D::Divide(const Vector2D & vec)
{
	this->x /= vec.x;
	this->y /= vec.y;
	return *this;
}


Vector2D& Vector2D::Zero()
{
	this->x = 0;
	this->y = 0;
	return *this;
}

Vector2D & Vector2D::operator+=(const Vector2D & vec)
{
	return this->Add(vec);
}

Vector2D & Vector2D::operator-=(const Vector2D & vec)
{
	return this->Subtract(vec);
}

Vector2D & Vector2D::operator*=(const Vector2D & vec)
{
	return this->Multiply(vec);
}

Vector2D & Vector2D::operator/=(const Vector2D & vec)
{
	return this->Divide(vec);
}

float Vector2D::Length() const
{
	return sqrt(x * x + y * y);
}

float Vector2D::LengthSquared() const
{
	return x * x + y * y;
}

float Vector2D::Distance(const Vector2D & vec) const
{
	return sqrt(((x - vec.x) * (x - vec.x)) + ((y - vec.y) * (y - vec.y)));
}

float Vector2D::Dot(const Vector2D & vec) const
{
	return x * vec.x + y * vec.y;
}

Vector2D & Vector2D::Normalize()
{
	{
		if (Length() != 0)
		{
			float length = Length();
			x /= length; y /= length;
			return *this;
		}

		x = y = 0;
		return *this;
	}

}

bool Vector2D::operator!=(const Vector2D & v)
{
	if (this->x == v.x && this->y == v.y) return false;
	else return true;
}

bool Vector2D::operator!=(const float& f)
{
	if (this->x == f && this->y == f) return false;
	else return true;
}

Vector2D & operator+(Vector2D & v1, const Vector2D & v2)
{
	return v1.Add(v2);
}

Vector2D & operator-(Vector2D & v1, const Vector2D & v2)
{
	return v1.Subtract(v2);
}

Vector2D & operator*(Vector2D & v1, const Vector2D & v2)
{
	return v1.Multiply(v2);
}

Vector2D & operator/(Vector2D & v1, const Vector2D & v2)
{
	return v1.Divide(v2);
}

std::ostream & operator<<(std::ostream & stream, const Vector2D & vec)
{
	stream << "{" << vec.x << "," << vec.y << "}";
	return stream;
}
