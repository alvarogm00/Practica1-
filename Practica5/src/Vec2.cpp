#include "Vec2.h"
#include <math.h>

Vec2::Vec2(float x, float y) : m_x(x), m_y(y)
{
}

Vec2::Vec2() : m_x(0.0f), m_y(0.0f)
{
}

Vec2& Vec2::operator=(const Vec2& other)
{
	m_x = other.m_x;
	m_y = other.m_y;
	return *this;
}

Vec2 Vec2::operator+(const Vec2& other) const
{
	return Vec2(m_x + other.m_x, m_y + other.m_y);
}

Vec2 Vec2::operator+(const int& other) const
{
	return Vec2(m_x + other, m_y + other);
}

Vec2 Vec2::operator-(const Vec2& other) const
{
	return Vec2(m_x - other.m_x, m_y - other.m_y);
}

Vec2 Vec2::operator-(const int& other) const
{
	return Vec2(m_x + other, m_y + other);
}

Vec2 Vec2::operator*(const Vec2& other) const
{
	return Vec2(m_x * other.m_x, m_y * other.m_y);
}

Vec2 Vec2::operator*(const float& other) const
{
	return Vec2(m_x * other, m_y * other);
}

float Vec2::scalar(const Vec2& other) const
{
	return m_x * other.m_x + m_y * other.m_y;
}

Vec2 Vec2::operator/(const int& other) const
{
	return Vec2(m_x / other, m_y / other);
}

Vec2 Vec2::operator/(const Vec2& other) const
{
	return Vec2(m_x/other.m_x, m_y/other.m_y);
}

Vec2 Vec2::abs() const
{
	float auxX = m_x;
	float auxY = m_y;
	if (auxX < 0) auxX *= -1;
	if (auxY < 0) auxY *= -1;
	return Vec2(auxX, auxY);
}

float Vec2::length() const
{
	return static_cast<float>(sqrt(m_x*m_x + m_y*m_y));
}

Vec2 Vec2::normalize() const
{
	float module = length();
	if (module == 0) return Vec2(0, 0);
	float x = m_x / module;
	float y = m_y / module;
	return Vec2(x, y);
}

float Vec2::angle(const Vec2& other) const
{
	return static_cast<float>(atan2(other.m_y-m_y, other.m_x-m_x));
}

float Vec2::distance(const Vec2& other) const
{
	Vec2 dif = Vec2(m_x - other.m_x, m_y - other.m_y);
	return dif.length();
}
