#include "GameCamera.h"

GameCamera::GameCamera() {}

GameCamera::GameCamera(Camara* _handle, TerrenoRR* _land) {
	handle = _handle;
	land = _land;
}

GameCamera::~GameCamera() {  }

Camara* GameCamera::getHandle() {
	return handle;
}

void GameCamera::render() {
	// Ajusto a 360deg
	normalizeRotation();
	float* fpos = new float[3] { position.x, position.y, position.z };
	float* frot = new float[2] { rotation.x, rotation.y };
	float* foff = new float[3] { offset.x, offset.y, offset.z };
	handle->UpdateCam(fpos, frot, foff);
	delete[] fpos;
	delete[] frot;
	delete[] foff;
}

GameCamera& GameCamera::setPosition2D(Vector2 _position) {
	position.x = _position.x;
	position.z = _position.y;
	position.y = land->Superficie(position.x, position.z);
	return *this;
}

GameCamera& GameCamera::setPosition2D(float _x, float _y) {
	return setPosition2D(Vector2(_x, _y));
}

GameCamera& GameCamera::translate2D(Vector2 offset2D) {
	Vector2 newPosition = offset2D + getPosition2D();
	setPosition2D(newPosition);
	return *this;
}

GameCamera& GameCamera::move2D(Vector2 direction2D) {
	direction2D = direction2D.normalize();
	Vector2 offset2D = direction2D * speed;
	translate2D(offset2D);
	return *this;
}

Vector2 GameCamera::getDirection() const {
	float yawRad = rotation.y * (PI / 180.0f);
	Vector2 temp;
	temp.x = sinf(yawRad);
	temp.y = cosf(yawRad);
	Vector2 direction = temp.normalize();
	return direction;
}

GameCamera& GameCamera::normalizeRotation() {
	rotation.x = fmod(rotation.x, 360.0f);
	rotation.y = fmod(rotation.y, 360.0f);
	return *this;
}