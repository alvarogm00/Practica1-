#pragma once
class Vec2
{
public:

	Vec2(float x, float y);
	Vec2();

	Vec2& operator=(const Vec2& other);

	Vec2 operator+(const Vec2& other) const;
	Vec2 operator+(const int& other) const;

	Vec2 operator-(const Vec2& other) const;
	Vec2 operator-(const int& other) const;

	Vec2 operator*(const Vec2& other) const;
	Vec2 operator*(const float& other) const;
	float scalar(const Vec2& other) const;

	Vec2 operator/(const int& other) const;
	Vec2 operator/(const Vec2& other) const;

	Vec2 abs() const;
	float length() const;
	Vec2 normalize() const;

	float angle(const Vec2& other) const;
	float distance(const Vec2& other) const;

	float m_x;
	float m_y;
};

