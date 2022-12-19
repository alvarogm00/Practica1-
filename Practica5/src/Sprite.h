#pragma once

#include <litegfx.h>
#include "Vec2.h"
#include <cstdint>

class Sprite
{
	// Tpo de la función callback
	typedef void (*CallbackFunc)(Sprite&, float);

public:
	// Indicamos el número de frames en horizontal y vertical
	// que tendrá la imagen del sprite
	Sprite(ltex_t* tex, int hframes = 1, int vframes = 1);

	~Sprite();

	// Establecemos puntero a la función callback
	void setCallback(CallbackFunc func);

	// Puntero genérico a datos (normalmente introducimos aquí los datos
	// del sprite que se van a utilizar en la función callback)
	void* getUserData();

	void setUserData(void* data);

	const ltex_t* getTexture() const;

	void setTexture(ltex_t* tex, int hframes = 1, int vframes = 1);

	lblend_t getBlend() const;

	void setBlend(lblend_t mode);

	float getRed() const;

	float getGreen() const;

	float getBlue() const;

	float getAlpha() const;

	void setColor(float r, float g, float b, float a);

	const Vec2& getPosition() const;

	void setPosition(const Vec2& pos);

	float getAngle() const;

	void setAngle(float angle);

	const Vec2& getScale() const;

	void setScale(const Vec2& scale);

	// Tamaño de un frame multiplicado por la escala
	Vec2 getSize() const;

	// Este valor se pasa a ltex_drawrotsized en el pintado
	// para indicar el pivote de rotación
	const Vec2& getPivot() const;

	void setPivot(const Vec2& pivot);

	int getHframes() const;

	int getVframes() const;

	// Veces por segundo que se cambia el frame de animación
	int getFps() const;

	void setFps(int fps);

	// Frame actual de animación
	float getCurrentFrame() const;

	void setCurrentFrame(int frame);

	void update(float deltaTime);

	void draw() const;

	void setFlip(bool flip);

	bool getFlip();

private:
	ltex_t* m_texture;

	void* m_data;
	CallbackFunc m_func;

	lblend_t m_blendMode;

	Vec2 m_pivot;
	Vec2 m_scale;
	Vec2 m_position;
	float m_angle;

	unsigned int m_hFrames;
	unsigned int m_vFrames;
	unsigned int m_currentFrame;
	int m_fps;
	bool m_flip;
	
	float m_acumTime;
	float m_u_unit;
	float m_v_unit;

	float m_r;
	float m_g;
	float m_b;
	float m_a;

	unsigned char* m_pixels;
};

