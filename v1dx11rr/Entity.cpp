#include "Entity.h"

Vector2 Entity::getPosition2D() {
	return Vector2(position.x, position.z);
}

Entity& Entity::setPosition(Vector3 _position) {
	position = _position;
	return *this;
}

Entity& Entity::setPosition(float _x, float _y, float _z) {
	return setPosition(Vector3(_x, _y, _z));
}

void Entity::setAttribute(string name, float value) {
	attributes[name] = value;
}

float Entity::getAttribute(string name) {
	if (!hasAttribute(name)) return 0;
	return attributes[name];
}

int Entity::getIntAttribute(string name) {
	if (!hasAttribute(name)) return 0;
	return (int)attributes[name];
}

bool Entity::getBoolAttribute(string name) {
	int value = getIntAttribute(name);
	return value != 0;
}

bool Entity::hasAttribute(string name) {
	auto it = attributes.find(name);
	return it != attributes.end();
}

Entity& Entity::translate(Vector3 offset) {
	Vector3 newPosition = offset + position;
	position = newPosition;
	return *this;
}

Entity& Entity::translateX(float offsetX) {
	position.x += offsetX;
	return *this;
}

Entity& Entity::translateY(float offsetY) {
	position.y += offsetY;
	return *this;
}

Entity& Entity::translateZ(float offsetZ) {
	position.z += offsetZ;
	return *this;
}

Entity& Entity::move(Vector3 direction) {
	direction = direction.normalize();
	Vector3 offset = direction * speed;
	translate(offset);
	return *this;
}