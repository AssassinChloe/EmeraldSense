#include "Vector2D.hpp"

Vector2D::Vector2D(): x(0), y(0){}

Vector2D::Vector2D(float x, float y): x(x), y(y) {}

Vector2D& Vector2D::add(const Vector2D& vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return (*this);
}
Vector2D& Vector2D::subtract(const Vector2D& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return (*this);
}
Vector2D& Vector2D::multiply(const Vector2D& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;
	return (*this);
}
Vector2D& Vector2D::divide(const Vector2D& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;
	return (*this);
}

Vector2D& operator+(Vector2D& v1, const Vector2D& v2)
{
	return v1.add(v2);
}
Vector2D& operator-(Vector2D& v1, const Vector2D& v2)
{
	return v1.subtract(v2);
}
Vector2D& operator*(Vector2D& v1, const Vector2D& v2)
{
	return v1.multiply(v2);
}
Vector2D& operator/(Vector2D& v1, const Vector2D& v2)
{
	return v1.divide(v2);
}

Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	return this->add(vec);
}
Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	return this->subtract(vec);
}
Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
	return this->multiply(vec);
}
Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
	return this->divide(vec);
}

Vector2D& Vector2D::operator*(const int& i)
{
	this->x *= i;
	this->y *= i;
	return *this;
}

bool Vector2D::operator==(const Vector2D& vec)
{
	if (this->x == vec.x && this->y == vec.y)
		return true;
	return false;
}
bool Vector2D::operator!=(const Vector2D& vec)
{
	if (this->x != vec.x || this->y != vec.y)
		return true;
	return false;
}
Vector2D& Vector2D::Zero()
{
	this->x = 0;
	this->y = 0;
	return (*this);
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vec)
{
	stream << "(" << vec.x << "," << vec.y << ")";
	return stream;
}
