#include "GameObject.h"

Game game;

GameObject::GameObject(ModeloRR* _handle) {
	handle = _handle;
}

GameObject::~GameObject() {
	delete handle;
}

ModeloRR* GameObject::getHandle() {
	return handle;
}

void GameObject::render() {
	if (hide) return;
	normalizeRotation();

	Camara* camara = game.camera.getHandle();
	float* hrotation = new float[3] { 
		rotation.x * (PI / 180.0f),
		rotation.y * (PI / 180.0f),
		rotation.z * (PI / 180.0f)
	};
	float* hscale = new float[3] { scale.x, scale.y, scale.z };
	handle->Draw(
		camara->vista, 
		camara->proyeccion, 
		position.x, 
		position.z, 
		position.y, 
		camara->posCam, 
		10.0f,
		hrotation, 
		hscale,
		1.0f
	);
	delete[] hscale;
	delete[] hrotation;
}

GameObject& GameObject::setPosition2D(Vector2 _position) {
	position.x = _position.x;
	position.z = _position.y;
	position.y = game.surface(position.x, position.z);
	return *this;
}

GameObject& GameObject::setPosition2D(float _x, float _y) {
	return setPosition2D(Vector2(_x, _y));
}

GameObject& GameObject::setScale(float _scale) {
	scale = Vector3(_scale, _scale, _scale);
	return *this;
}

GameObject& GameObject::translate2D(Vector2 offset2D) {
	Vector2 newPosition = offset2D + getPosition2D();
	setPosition2D(newPosition);
	return *this;
}

GameObject& GameObject::move2D(Vector2 direction2D) {
	direction2D = direction2D.normalize();
	Vector2 offset2D = direction2D * speed;
	translate2D(offset2D);
	return *this;
}

GameObject& GameObject::normalizeRotation() {
	rotation.x = fmod(rotation.x, 360.0f);
	rotation.y = fmod(rotation.y, 360.0f);
	rotation.z = fmod(rotation.z, 360.0f);
	return *this;
}