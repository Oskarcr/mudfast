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
	Vector3 position = Vector3(0.0f, 0.0f, 0.0f);

	// La rotacion en tres ejes de la Entity.
	//Vector3 rotation = Vector3(0.0f, 180.0f, 0.0f);

	// La escala en tres ejes de la Entity.
	//Vector3 scale = Vector3(1.0f, 1.0f, 1.0f);

	// Devuelve un Vector2 con las coordenadas (x, z) correspondientes.
	Vector2 getPosition2D();

	// Establece la posicion (x, y, z) del objeto y devuelve la Entity.
	Entity& setPosition(Vector3 _position);

	// Establece la posicion (x, y, z) del objeto y devuelve la Entity.
	Entity& setPosition(float _x, float _y, float _z);

	// Establece un attributo de la entidad
	void setAttribute(string name, float value);

	// Obtiene el valor de un atributo de la entidad.
	float getAttribute(string name);

	// Devuelve true si la entidad tiene el atributo especificado.
	// En caso contrario devuelve false.
	bool hasAttribute(string name);
};