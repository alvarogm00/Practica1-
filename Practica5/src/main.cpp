#include "Sprite.h"

#define LITE_GFX_IMPLEMENTATION
#include <litegfx.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glfw3.h>
#include <iostream>
#include "Vec2.h"

using namespace std;
Vec2 mousePos;

void mouseMoved(GLFWwindow* window, double xpos, double ypos) {
	mousePos.m_x = static_cast<float>(xpos);
	mousePos.m_y = static_cast<float>(ypos);
}

ltex_t* loadTexture(const char* filename) {
	int imgW, imgH;
	unsigned char* data;

	ltex_t* aux;

	data = stbi_load(filename, &imgW, &imgH, nullptr, 4);
	aux = ltex_alloc(imgW, imgH, 0);
	ltex_setpixels(aux, data);
	stbi_image_free(data);

	return aux;
}

void beeMovement(Sprite& sprite, float deltaTime) {
	Vec2 beePos = sprite.getPosition();
	float beeAngle = sprite.getAngle();
	float movSpeed = 128.0f;
	float rotSpeed = 32.0f;

	Vec2* mouse = static_cast<Vec2*>(sprite.getUserData());
	Vec2 dir = *mouse - beePos;
	if (dir.length() > 5) {
		dir = dir.normalize();
		beePos = beePos + dir * (movSpeed * deltaTime);
	}

	if (dir.m_x > 0) {
		if((*mouse - beePos).length() > 5)sprite.setFlip(false);
		if(beeAngle > -15.0f)
			beeAngle -= (rotSpeed * deltaTime);
	}
	else if (dir.m_x < 0) {
		if ((*mouse - beePos).length() > 5)sprite.setFlip(true);
		if(beeAngle < 15.0f)
			beeAngle += (rotSpeed * deltaTime);
	}
	else {
		if (beeAngle < 0) beeAngle += (rotSpeed * deltaTime);
		if (beeAngle > 0) beeAngle -= (rotSpeed * deltaTime);
	}
	sprite.setPosition(beePos);
	sprite.setAngle(beeAngle);
}

int main() {
	
	//-------------------Inicializacion

	//Iniciamos GFWX
	int err = glfwInit();
	if (!err) printf("Error al inicializar glfw\n");

	//Iniciamos la ventana
	Vec2 window_size = Vec2(900, 600);
	Vec2 window_center = Vec2(window_size.m_x / 2, window_size.m_y / 2);
	GLFWwindow* window = glfwCreateWindow(static_cast<int>(window_size.m_x), static_cast<int>(window_size.m_y), "Practica 4", nullptr, nullptr);
	if (!window) printf("Error al crear la ventana\n");

	//Asociamos contexto a ventana
	glfwMakeContextCurrent(window);
	//Iniciamos LiteGFX
	lgfx_setup2d(static_cast<int>(window_size.m_x), static_cast<int>(window_size.m_y));

	//-------------------Carga de recursos
	ltex_t* beeText = loadTexture("bee_anim.png");
	Sprite* beeSprite = new Sprite(beeText, 8, 1);
	beeSprite->setFps(8);
	beeSprite->setPivot(Vec2(0.5f, 0.5f));
	beeSprite->setCallback(beeMovement);
	beeSprite->setUserData(&mousePos);

	//------------------Logica

	glfwSetCursorPosCallback(window, mouseMoved);

	//------------------Bucle ppal

	double lastTime = 0;
	double deltaTime;
	while (!glfwWindowShouldClose(window)) {
		//Actualizamos delta
		deltaTime = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();

		//Leemos input

		//Actualizamos logica
		beeSprite->update(deltaTime);

		//Limpiamos BackBuffer
		lgfx_clearcolorbuffer(0.15, 0.15, 0.15);

		//Renderizamos la escena
		beeSprite->draw();

		//Cambio buffers
		glfwSwapBuffers(window);

		//Procesar eventos
		glfwPollEvents();
	}

	//Liberamos memoria
	delete beeSprite;

	//Cerramos libreria
	glfwTerminate();

	return 0;
}
