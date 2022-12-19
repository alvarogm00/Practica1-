#pragma once
#include "../src/Vec2.h"
#include <cstdint>

class CCollider
{
public:
	virtual bool collides(const CCollider& other) const = 0;
	virtual bool collides(const Vec2& circlePos, float circleRadius) const = 0; 
	virtual bool collides(const Vec2& rectPos, const Vec2& rectSize) const = 0; 
	virtual bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const = 0;

protected:
	static bool checkCircleCircle(const Vec2& pos1, float radius1, const Vec2& pos2, float radius2); 
	static bool checkCircleRect(const Vec2& circlePos, float circleRadius, const Vec2& rectPos, const Vec2& rectSize);
	static bool checkRectRect(const Vec2& rectPos1, const Vec2& rectSize1, const Vec2& rectPos2, const Vec2& rectSize2);
	static bool checkCirclePixels(const Vec2& circlePos, float circleRadius, const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels);
	static bool checkPixelsPixels(const Vec2& pixelsPos1, const Vec2& pixelsSize1, const uint8_t* pixels1, const Vec2& pixelsPos2, const Vec2& pixelsSize2, const uint8_t* pixels2);
	static bool checkPixelsRect(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels, const Vec2& rectPos, const Vec2& rectSize);

	Vec2 m_pos;

private:
	static float Clamp(float _value, float _minvalue, float _maxValue);
};

class CCircleCollider : CCollider
{
	// Inherited via CCollider
	virtual bool collides(const CCollider& other) const override;
	virtual bool collides(const Vec2& circlePos, float circleRadius) const override;
	virtual bool collides(const Vec2& rectPos, const Vec2& rectSize) const override;
	virtual bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const override;

private: 
	float m_radius;
};

class CRectCollider : CCollider
{
	// Inherited via CCollider
	virtual bool collides(const CCollider& other) const override;
	virtual bool collides(const Vec2& circlePos, float circleRadius) const override;
	virtual bool collides(const Vec2& rectPos, const Vec2& rectSize) const override;
	virtual bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const override;

private:

	float m_width;
	float m_height;
	Vec2 m_size;
};

class CPixelsCollider : CCollider
{
	// Inherited via CCollider
	virtual bool collides(const CCollider& other) const override;
	virtual bool collides(const Vec2& circlePos, float circleRadius) const override;
	virtual bool collides(const Vec2& rectPos, const Vec2& rectSize) const override;
	virtual bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const override;

private:
	Vec2 m_size;
};