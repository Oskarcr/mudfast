#include "Game.h"

#include <dinput.h>

void Game::input(char* keyboardData) {
	if (settings.inputEnabled == false) return;

	if (keyboardData[DIK_ESCAPE] & 0x80) {
		HWND hwnd = GetActiveWindow();
		KillTimer(hwnd, 100);
		PostQuitMessage(0);
		return;
	}

	// Rotacion de la camra del jugador 
	float mouseDeltaX = getMouseDeltaPosition().x;
	
	if (mouseDeltaX > settings.mouseDeltaThreshold || mouseDeltaX < -settings.mouseDeltaThreshold) {
		camera.rotation.y += getMouseDeltaPosition().x * -(settings.mouseSensitivity);
	}

	float screenMiddleHeight = getScreenSize().y / 2.0f;
	float xScale = (getMousePosition().y - screenMiddleHeight) / screenMiddleHeight;
	camera.rotation.x = settings.maxAngleX * xScale + settings.offsetAngleX;

	// Movimiento de la camra del jugador
	float radians = camera.rotation.y * (PI / 180.0f);

	bool inVehicle = camera.getBoolAttribute("in_vehicle");

	Vector2 offset;
	if (inVehicle) {
		GameObject& van = getObjectById("Van");
		Vector2 directionFront = camera.getDirection();

		if ((keyboardData[DIK_E] & 0x80)) {
			camera.setAttribute("in_vehicle", false);
			camera.translate2D(directionFront * 35);
			return;
		}

		Vector2 directionVan = van.getDirection2D();

		Vector2 direction = (directionVan * 3 + directionFront).normalize();

		//Vector2 


		float speed = 0.0f;
		if ((keyboardData[DIK_W] & 0x80) || (keyboardData[DIK_UP] & 0x80)) {
			speed += 1.0f;
		}
		if ((keyboardData[DIK_S] & 0x80) || (keyboardData[DIK_DOWN] & 0x80)) {
			speed += -0.6f;
		}
		if (speed == 0) return;


		camera.speed = settings.speedVehicle * speed * deltaTime;

		van.rotation.y = atan2(direction.x, direction.y) * (180.f / PI);
		camera.move2D(direction);
		/*
		if ((keyboardData[DIK_W] & 0x80) || (keyboardData[DIK_UP] & 0x80)) {
			offset.x += sinf(radians) * settings.speedFront * settings.speedVehicle;
			offset.y += cosf(radians) * settings.speedFront * settings.speedVehicle;
		}

		if ((keyboardData[DIK_S] & 0x80) || (keyboardData[DIK_DOWN] & 0x80)) {
			offset.x -= sinf(radians) * settings.speedBack;
			offset.y -= cosf(radians) * settings.speedBack;
		}*/
		return;
	}

	if ((keyboardData[DIK_W] & 0x80) || (keyboardData[DIK_UP] & 0x80)) {
		const float vel = (!(keyboardData[DIK_LSHIFT] & 0x80)) ? 1.0f : settings.sprintMultiplier;
		offset.x += sinf(radians) * settings.speedFront * vel;
		offset.y += cosf(radians) * settings.speedFront * vel;
	}

	if ((keyboardData[DIK_S] & 0x80) || (keyboardData[DIK_DOWN] & 0x80)) {
		offset.x -= sinf(radians) * settings.speedBack;
		offset.y -= cosf(radians) * settings.speedBack;
	}

	if ((keyboardData[DIK_A] & 0x80) || (keyboardData[DIK_LEFT] & 0x80)) {
		offset.x -= sinf(radians + (PI * 0.5f)) * settings.speedLeftRight;
		offset.y -= cosf(radians + (PI * 0.5f)) * settings.speedLeftRight;
	}

	if ((keyboardData[DIK_D] & 0x80) || (keyboardData[DIK_RIGHT] & 0x80)) {
		offset.x += sinf(radians + (PI * 0.5f)) * settings.speedLeftRight;
		offset.y += cosf(radians + (PI * 0.5f)) * settings.speedLeftRight;
	}

	// Movimiento de la camara del jugador
	camera.translate2D(offset * deltaTime);
}