#include "GameBillboard.h"

GameBillboard::GameBillboard(BillboardRR* _handle) {
	handle = _handle;
}

GameBillboard::~GameBillboard() {
	delete handle;
}

BillboardRR* GameBillboard::getHandle() {
	return handle;
}

void GameBillboard::render() {
	if (hide) return;

	Camara* camara = game.camera.getHandle();
	Vector2 frameMinUV = getFrameMinUV();
	Vector2 frameMaxUV = getFrameMaxUV();
	// Este no es mi Vector2, pero lo agarro por compatibilidad
	// Sacamos las UVs del frame.

	vector2 uv1;
	uv1.u = frameMinUV.x;
	uv1.v = frameMaxUV.y;
	vector2 uv2;
	uv2.u = frameMinUV.x;
	uv2.v = frameMinUV.y;
	vector2 uv3;
	uv3.u = frameMaxUV.x;
	uv3.v = frameMinUV.y;
	vector2 uv4;
	uv4.u = frameMaxUV.x;
	uv4.v = frameMaxUV.y;

	// Dibujamos el billboard
	handle->Draw(
		camara->vista, 
		camara->proyeccion,
		camara->posCam, 
		position.x, 
		position.z, 
		position.y,
		size,
		uv1,
		uv2,
		uv3,
		uv4
	);
}

void GameBillboard::setFrameData(int _rows, int _columns, int _maxFrame) {
	if (_rows < 1|| _columns < 1|| _maxFrame < 1) return;
	rows = _rows;
	columns = _columns;
	sizeUV = Vector2(1.f / (float)columns, 1.f / (float)rows);
	maxFrame = _maxFrame;
}

void GameBillboard::nextFrame() {
	currentFrame++;
	if (currentFrame >= maxFrame) currentFrame = 0;
}

Vector2 GameBillboard::getFrameMinUV() {
	int col = currentFrame % columns;
	int row = currentFrame / columns;

	//int row = rows - 1 - (currentFrame / columns);
	return Vector2(col, row) * sizeUV;
}

Vector2 GameBillboard::getFrameMaxUV() {
	return getFrameMinUV() + sizeUV;
}

Vector2 GameBillboard::getSizeUV() {
	return sizeUV;
}

GameBillboard& GameBillboard::setPosition2D(Vector2 _position) {
	position.x = _position.x;
	position.z = _position.y;
	position.y = game.surface(position.x, position.z);
	return *this;
}

GameBillboard& GameBillboard::setPosition2D(float _x, float _y) {
	return setPosition2D(Vector2(_x, _y));
}

GameBillboard& GameBillboard::translate2D(Vector2 offset2D) {
	Vector2 newPosition = offset2D + getPosition2D();
	setPosition2D(newPosition);
	return *this;
}

GameBillboard& GameBillboard::move2D(Vector2 direction2D) {
	direction2D = direction2D.normalize();
	Vector2 offset2D = direction2D * speed;
	translate2D(offset2D);
	return *this;
}