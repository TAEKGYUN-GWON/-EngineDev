#include "stdafx.h"
#include "Vector2.h"
Vector2 Vector2::zero = Vector2(0, 0);
Vector2 Vector2::up = Vector2(0, -1);
Vector2 Vector2::down = Vector2(0, 1);
Vector2 Vector2::left = Vector2(-1, 0);
Vector2 Vector2::right = Vector2(1, 0);
Vector2 Vector2::one = Vector2(1, -1);


b2Vec2 Vector2::b2Up = b2Vec2(0, -1);
b2Vec2 Vector2::b2Down = b2Vec2(0, 1);
b2Vec2 Vector2::b2Right = b2Vec2(1, 0);
b2Vec2 Vector2::b2Left = b2Vec2(-1, 0);
b2Vec2 Vector2::b2Zero = b2Vec2(0, 0);
b2Vec2 Vector2::b2One = b2Vec2(1, -1);

Vector2 Vector2::operator-(Vector2 to)
{
	
	return Vector2(x-to.x,y-to.y);
}

bool Vector2::operator<(const Vector2& to) const
{
	int a = to.x - to.y;
	int b = x - y;
	float32 me = x * x*x + y * y*y;
	float32 other = to.x*to.x*to.x + to.y*to.y*to.y;

	return me * a < other*b;

}

bool Vector2::operator>(const Vector2& to)const
{

	return x > to.x && y > to.y;
}

bool Vector2::operator<=(const Vector2 & to) const
{
	return x <= to.x && y <= to.y;
}

bool Vector2::operator>=(const Vector2 & to) const
{
	return x >= to.x && y >= to.y;
}

float Vector2::operator|(const Vector2 & to) const
{
	return x * to.x + y * to.y;
}

float Vector2::operator^(const Vector2 & to) const
{
	return x * to.y + y * to.x;
}

Vector2 Vector2::operator+(Vector2 to)
{
	return Vector2(x + to.x, y + to.y);
}

Vector2 Vector2::operator*(float to)
{
	return Vector2(x *to, y*to);
}

Vector2 Vector2::operator/(int to)
{
	return Vector2(x/to,y/to);
}

void Vector2::operator+=(Vector2 to)
{
	x += to.x;
	y += to.y;
}

void Vector2::operator-=(Vector2 to)
{
	x -= to.x;
	y -= to.y;
}

bool Vector2::operator==(Vector2 to) const
{
	return x == to.x && y == to.y;
}
bool Vector2::operator!=(Vector2 to) const
{
	return x != to.x || y != to.y;
}

float Vector2::Magnitude()
{
	return sqrt(x * x + y * y);
}

Vector2 Vector2::Nomalized()
{
	//Vector2 result;
	//float size = SqrMagnitude();

	//if (!size)	
	//	return Vector2::zero;

	//this->x /= size;
	//this->y /= size;


	const float SquareSum = x * x + y * y;
	if (SquareSum > 0)
	{
		const float Scale = sqrt(SquareSum);
		x *= Scale;
		y *= Scale;
		return *this;
	}

	x = 0.0f;
	y = 0.0f;

	return *this;
}

float Vector2::SqrMagnitude()
{
	return (x * x + y * y);
}

Vector2 Vector2::RotateToDegree(float angle)
{
	float newX = x * cos(angle*RadToDeg) - y * sin(angle*RadToDeg);
	float newY = y * cos(angle*RadToDeg) + x* sin(angle*RadToDeg);

	return Vector2(newX, newY);
}

Vector2 Vector2::RotateToRadian(float angle)
{
	float newX = x * cos(angle) - y * sin(angle);
	float newY = y * cos(angle) + x * sin(angle);

	return Vector2(newX, newY);
}


float Vector2::Distance(Vector2 a, Vector2 b, bool check)
{
	float x = b.x - a.x;
	float y = b.y - a.y;

	if(check)
		return sqrtf(x * x + y * y);
	else return x * x + y * y;
}

float Vector2::Dot(Vector2 lhs, Vector2 rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

Vector2 Vector2::Lerp(Vector2 a, Vector2 b, float i)
{
	float x = (1 - i)*a.x + i * b.x;
	float y = (1 - i)*a.y + i * b.y;

	return Vector2(x, y);
}
