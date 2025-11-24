#pragma once

#include "Game.h"

class GameObject : public Entity {
private:
	ModeloRR* handle;
	
public:
	// La rotacion en tres ejes del objeto.
	Vector3 rotation = Vector3(0, 0, 0);

	// La escala en tres ejes del objeto.
	Vector3 scale = Vector3(1, 1, 1);

	// Si el objeto esta oculto.
	bool hide = false;

	GameObject(ModeloRR* _handle);

	~GameObject();

	// Devuelve el puntero interno.
	ModeloRR* getHandle();

	// Renderiza el objeto.
	void render();

	// Devuelve el mismo GameObject y establece la posicion en 2D de la Entity tomando en cuenta la altura del terreno.
	GameObject& setPosition2D(Vector2 _position);

	// Devuelve el mismo GameObject y establece la posicion en 2D de la Entity tomando en cuenta la altura del terreno.
	GameObject& setPosition2D(float _x, float _y);

	// Establece una misma escala en los tres ejes.
	GameObject& setScale(float _scale);

	// Desplaza la entidad instantaneamente las unidades indicadas tomando en cuenta la altura del terreno.
	GameObject& translate2D(Vector2 offset2D);

	// Desplaza la entidad instantaneamente en una direccion mediante su speed tomando en cuenta la altura del terreno.
	// Se desplazara "speed" unidades hacia "direction".
	GameObject& move2D(Vector2 direction);
};