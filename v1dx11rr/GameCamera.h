#pragma once

#include "Entity.h"
#include "TerrenoRR.h"
#include "Camara.h"

class GameCamera : public Entity {
private:
	Camara* handle = nullptr;
	TerrenoRR* land = nullptr;
public:
	// El desplazamiento en los tres ejes de la camara.
	Vector3 offset = Vector3(0, 0.04f, 0);

	// La rotacion de la camara
	Vector2 rotation = Vector2(0, 0);

	GameCamera();

	GameCamera(Camara * _handle, TerrenoRR * _land);

	~GameCamera();

	// Renderiza la vista de la camara.
	void render();

	// Devuelve el puntero de la camara.
	Camara* getHandle();

	// Devuelve el mismo GameCamera y establece la posicion en 2D de la Entity tomando en cuenta la altura del terreno.
	GameCamera& setPosition2D(Vector2 _position);

	// Devuelve el mismo GameCamera y establece la posicion en 2D de la Entity tomando en cuenta la altura del terreno.
	GameCamera& setPosition2D(float _x, float _y);

	// Desplaza la entidad instantaneamente las unidades indicadas tomando en cuenta la altura del terreno.
	GameCamera& translate2D(Vector2 offset2D);

	// Desplaza la entidad instantaneamente en una direccion mediante su speed tomando en cuenta la altura del terreno.
	// Se desplazara "speed" unidades hacia "direction".
	GameCamera& move2D(Vector2 direction);

	// Devuelve la direccion2D en la que el jugador esta viendo.
	Vector2 getDirection() const;

	// Normaliza la rotacion de 0 - 360.
	GameCamera& normalizeRotation();
};