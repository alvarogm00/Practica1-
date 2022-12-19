#include "Sprite.h"
#include <iostream>

Sprite::Sprite(ltex_t* tex, int hframes, int vframes) : m_texture(tex), m_hFrames(static_cast<unsigned int>(hframes)), m_vFrames(static_cast<unsigned int>(vframes)),
	m_data(nullptr), m_pivot(Vec2(0,0)), m_scale(Vec2(1,1)), m_position(Vec2(0,0)), m_angle(0.0f), m_currentFrame(0), m_fps(24), m_acumTime(0),
	m_r(1), m_g(1), m_b(1), m_a(1), m_func(nullptr), m_blendMode(BLEND_ALPHA), m_u_unit(1.0f / m_hFrames), m_v_unit(1.0f / m_vFrames), m_flip(false), m_pixels(nullptr)
{
}

Sprite::~Sprite()
{
	ltex_free(m_texture);
}

void Sprite::setCallback(CallbackFunc func)
{
	m_func = func;
}

void* Sprite::getUserData()
{
	return m_data;
}

void Sprite::setUserData(void* data)
{
	m_data = data;
}

const ltex_t* Sprite::getTexture() const
{
	return m_texture;
}

void Sprite::setTexture(ltex_t* tex, int hframes, int vframes)
{
	m_texture = tex;
	m_hFrames = hframes;
	m_vFrames = vframes;

	m_u_unit = 1.0f / m_hFrames;
	m_v_unit = 1.0f / m_vFrames;

	ltex_setpixels(tex, (m_pixels));
}

lblend_t Sprite::getBlend() const
{
	return m_blendMode;
}

void Sprite::setBlend(lblend_t mode)
{
	m_blendMode = mode;
}

float Sprite::getRed() const
{
	return m_r;
}

float Sprite::getGreen() const
{
	return m_g;
}

float Sprite::getBlue() const
{
	return m_b;
}

float Sprite::getAlpha() const
{
	return m_a;
}

void Sprite::setColor(float r, float g, float b, float a)
{
	m_r = r;
	m_g = g;
	m_b = b;
	m_a = a;
}

const Vec2& Sprite::getPosition() const
{
	return m_position;
}

void Sprite::setPosition(const Vec2& pos)
{
	m_position = pos;
}

float Sprite::getAngle() const
{
	return m_angle;
}

void Sprite::setAngle(float angle)
{
	m_angle = angle;
}

const Vec2& Sprite::getScale() const
{
	return m_scale;
}

void Sprite::setScale(const Vec2& scale)
{
	m_scale = scale;
}

Vec2 Sprite::getSize() const
{
	float width = m_texture->width / static_cast<float>(m_hFrames);
	float height = m_texture->height / static_cast<float>(m_vFrames);
	return Vec2(width * m_scale.m_x, height * m_scale.m_y);
}

const Vec2& Sprite::getPivot() const
{
	return m_pivot;
}

void Sprite::setPivot(const Vec2& pivot)
{
	m_pivot = pivot;
}

int Sprite::getHframes() const
{
	return m_hFrames;
}

int Sprite::getVframes() const
{
	return m_vFrames;
}

int Sprite::getFps() const
{
	return m_fps;
}

void Sprite::setFps(int fps)
{
	m_fps = fps;
}

float Sprite::getCurrentFrame() const
{
	return m_currentFrame;
}

void Sprite::setCurrentFrame(int frame)
{
	m_currentFrame = frame;
}

void Sprite::update(float deltaTime)
{
	if(m_func != nullptr)
		m_func(*this, deltaTime);

	float timePerFrame = 1.0f / m_fps;
	float newTime = m_acumTime + deltaTime;

	int nFrames = static_cast<int>(newTime / timePerFrame);

	m_acumTime = newTime - (nFrames * timePerFrame);

	m_currentFrame += nFrames;
	m_currentFrame = m_currentFrame % (m_hFrames * m_vFrames);
}

void Sprite::draw() const
{
	lgfx_setblend(m_blendMode);
	lgfx_setcolor(m_r, m_g, m_b, m_a);

	unsigned int row = m_currentFrame % m_vFrames;
	unsigned int col = m_currentFrame - (m_hFrames * row);
	
	float u0 = m_u_unit * col;
	float u1 = m_u_unit * (col + 1);
	float v0 = m_v_unit * row;
	float v1 = m_v_unit * (row + 1);

	Vec2 size = getSize();

	if(m_flip)
		ltex_drawrotsized(m_texture, m_position.m_x, m_position.m_y, m_angle, m_pivot.m_x, m_pivot.m_y, size.m_x, size.m_y,
			u1, v0, u0, v1);
	else
		ltex_drawrotsized(m_texture, m_position.m_x, m_position.m_y, m_angle, m_pivot.m_x, m_pivot.m_y, size.m_x, size.m_y,
			u0, v0, u1, v1);
}

void Sprite::setFlip(bool flip)
{
	m_flip = flip;
}

bool Sprite::getFlip()
{
	return m_flip;
}
