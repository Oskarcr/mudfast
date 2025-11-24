#pragma once

#include "Vectors.h"
#include <unordered_map>

using namespace std;

class Entity {
private:
	// Los atributos de la entidad.
	unordered_map<string, float> attributes;
public:
	// La posicion en tres ejes de la Entity en el espacio y tiempo.
	Vector3 position = Vector3(0, 0, 0);

	// Devuelve un Vector2 con las coordenadas (x, z) correspondientes.
	Vector2 getPosition2D();

	// Establece la posicion (x, y, z) del objeto y devuelve la Entity.
	Entity& setPosition(Vector3 _position);

	// Establece la posicion (x, y, z) del objeto y devuelve la Entity.
	Entity& setPosition(float _x, float _y, float _z);

	// Establece un attributo de la entidad.
	// Es la base de los setAttributes's().
	void setAttribute(string name, float value);

	// Obtiene el valor de un atributo de la entidad en formato float.
	// Es el base de los getAttribute's().
	float getAttribute(string name);

	// Obtiene el valor de un atributo de la entidad en formato int.
	// Es simplemente un (int)getAttribute(name).
	int getIntAttribute(string name);

	// Obtiene el valor de un atributo de la entidad en formato bool.
	// Es simplemente un (int)getAttribute(name) != 0.
	bool getBoolAttribute(string name);

	// Devuelve true si la entidad tiene el atributo especificado.
	// En caso contrario devuelve false.
	bool hasAttribute(string name);
};