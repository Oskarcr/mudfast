#pragma once

#include "Game.h"

class GameBillboard : public Entity {
private:
	Vector2 sizeUV = Vector2(1, 1);
	int currentFrame = 0;
	int rows = 1;
	int columns = 1;
	int maxFrame = 0;

	BillboardRR* handle = nullptr;
public:
	// El tamano del billboard.
	float size = 1;

	GameBillboard(BillboardRR * _handle);
	~GameBillboard();

	// Devuelve el puntero interno.
	BillboardRR* getHandle();

	// Renderiza el billboard.
	void render();

	// Establece la informacion de la animacion de frames de un billboard.
	void setFrameData(int _rows, int _columns, int _maxFrame);

	// Incrementa currentFrame, lo que hace que se vea el siguiente frame del billboard (si tiene).
	// Si es mayor o igual a maxFrame entonces regresara a 0.
	void nextFrame();

	// Devuelve una coordenada (u, v) maxima del frame actual.
	Vector2 getFrameMaxUV();

	// Devuelve una coordenada (u, v) minima del frame actual.
	Vector2 getFrameMinUV();

	// Obtiene el tamano base del frame (u, v).
	Vector2 getSizeUV();

	// Devuelve el mismo GameBillboard y establece la posicion en 2D de la Entity tomando en cuenta la altura del terreno.
	GameBillboard& setPosition2D(Vector2 _position);

	// Devuelve el mismo GameBillboard y establece la posicion en 2D de la Entity tomando en cuenta la altura del terreno.
	GameBillboard& setPosition2D(float _x, float _y);
};