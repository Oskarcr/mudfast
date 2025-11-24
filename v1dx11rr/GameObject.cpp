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
	Camara* camara = game.getCamera();
	handle->Draw(
		camara->vista, 
		camara->proyeccion, 
		position.x, 
		position.z, 
		position.y, 
		camara->posCam, 
		10.0f, 
		0.f, 
		'Y',
		1.0f,
		1.0f
	);
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