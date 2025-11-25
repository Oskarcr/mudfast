#pragma once

// Entity y Vectors primero porque no dependen

#include "ModeloRR.h"
#include "Billboard.h"

class Game;
extern Game game;

#include "Entity.h"

#include "GamePlayer.h"
#include "GameObject.h"
#include "GameBillboard.h"
#include "GameCamera.h"

#include "Vectors.h"
#include <Windows.h>
#include <map>
#include <functional>
#include <chrono>

#include <iostream>

class GameObject;
class GameBillboard;
class GameCamera;

enum EntityType {
	OBJ_CAR_DEFAULT,
	OBJ_POLICE_CAR,
	OBJ_CAR_VAN,
	OBJ_BOX_SMALL,
	OBJ_BOX_MEDIUM,
	OBJ_BOX_BIG,
	OBJ_COCA_COLA_VENDING,
	OBJ_MATRESS,
	OBJ_BUSH,
	OBJ_SOFA,
	OBJ_TABLE,
	OBJ_GAS_BOMB,
	BILL_OBJETIVE,
	BILL_FIRE,
	BILL_EXPLOSION,
	BILL_CAT_CHAD,
	A_1,			//�RBOLES
	A_2,
	A_3,
	BILL_BUSH,
	MARRIDO,
	MARIDA,
	CASA_1,
	CASA_2,
	CASA_3,
	DEAD_SIG,
	STREET_L,
	ALMACEN_1,
	ALMACEN_2,
	EXPLORABLE_1,
	EXPLORABLE_2,
	SHOP_1,
	PERSONA1,
	PERSONA2,
	PERSONA3,
	PERSONA4,
	N_1,
	N_2,
	N_3,
	N_4,
	N_5,
	N_6,
	N_7,
	N_8,
	N_9,
	N_0,
};

using namespace chrono;

class Game {
private:
	steady_clock::time_point previousTime;
	steady_clock::time_point currentTime = steady_clock::now();

	ID3D11Device* d3dDevice = nullptr;
	ID3D11DeviceContext* d3dContext = nullptr;
	TerrenoRR* land = nullptr;

	map<string, GameObject*> objects;
	map<string, GameBillboard*> billboards;

	Vector2 lastMousePosition = Vector2(0, 0);
public: 
	struct Settings {
	public:
		// Variables de los shaders
		int maxDistance = 14000;
		int minDistance = 10000;

		// Movimiento x y z
		float sprintMultiplier = 1.5f;
		float speedFront = 32;
		float speedLeftRight = 28;
		float speedBack = 24;

		// Movimiento del mouse
		float mouseSensitivity = 0.028f;
		float mouseDeltaThreshold = 10.0f;
		float maxAngleX = 40.0f;
		float offsetAngleX = 10.0f;

		// Deshabilitar el input
		float inputEnabled = true;
	};

	Settings settings;

	// La diferencia de tiempo en segundos del frame anterior a este.
	float deltaTime = 0.f;

	// El tiempo transcurrido.
	float time = 0.f;

	// El volumen general del juego.
	float volume = 1.0f;

	// Si esta en modo test no cargara los modelos.
	bool testMode = false;

	// Si esta en modo debug la pantalla se hara chica.
	bool debugMode = false;

	// El reproductor de musica.
	GamePlayer player = GamePlayer();

	// La camara del jugador.
	GameCamera camera;

	Game();
	~Game();

	// Devuelve un Vector2 con la posicion del mouse (x, y) en
	// la pantalla entera.
	Vector2 getMousePosition();

	// Guarda la posicion del mouse (x, y) actual.
	Vector2 saveMousePosition();

	// Devuelve un Vector2 que representa la posicion delta del mouse (dx, dy) en el ultimo frame.
	Vector2 getMouseDeltaPosition();

	// Devuelve un Vector2 que representa (width, height) de la pantalla entera.
	Vector2 getScreenSize();

	// Establece la posicion (x, y) del mouse.
	void setMousePosition(Vector2 position);

	// Establece la posicion (x, y) del mouse.
	void setMousePosition(float x, float y);

	// Devuelve un float que es equivalente a la altura de la superficie del terreno en un punto (x, y).
	float surface(Vector2 position);

	// Devuelve un float que es equivalente a la altura de la superficie del terreno en un punto (x, y).
	float surface(float x, float y);

	// Establece la variable d3dContext.
	void setContext(ID3D11DeviceContext* _d3dContext);

	// Establece la variable d3dDevice.
	void setDevice(ID3D11Device* _d3dDevice);

	// Establece la variable camera.
	void setCamera(Camara* _camera);

	// Establece el terreno.
	void setLand(TerrenoRR * _land);

	// Devuelve el puntero del terreno.
	TerrenoRR* getLand();

	// Se llama cuando el programa esta preparado para que inicie.
	void start();

	// Se llama cuando inicia el programa en modo test.
	void test();

	// Se llama despues de cada render del programa
	void update();

	// Se llama despues de render y antes de update.
	// Es para el input.
	void input(char* keyboardData);

	// Se llama cada render del programa
	void render();

	// Actualiza el tiempo del juego.
	void updateTime();

	// Crea un objeto con una id en especifico y devuelve la referencia.
	// Si el objeto ya existe, generara un id igual pero como id+"_c".
	GameObject& createObject(string id, EntityType type);

	// Devuelve una referencia de un GameObject de la escena que tenga el id especificado.
	GameObject& getObjectById(string id);

	// Devuelve true si el objeto con el id especificado se encuentra en la escena. 
	// En caso contrario retorna false.
	bool hasObject(string id);

	// Crea un billboard con una id en especifico y devuelve la referencia.
	// Si el objeto ya existe, generara un id igual pero como id+"_c".
	GameBillboard& createBillboard(string id, EntityType type);

	// Devuelve una referencia de un GameBillboard de la escena que tenga el id especificado.
	GameBillboard& getBillboardById(string id);

	// Devuelve true si el billboard con el id especificado se encuentra en la escena. 
	// En caso contrario retorna false.
	bool hasBillboard(string id);

	// Devuelve el asset del entityType especificado.
	// Este metodo se tiene que modificar si quieren agregar modelos.
	string getAssetNameByEntityType(EntityType type);

	// Hace una funcion por cada objeto de la escena.
	// Es recomendable usarlo con moderacion.
	void forEachObjects(function<void(GameObject&)> callback);

	// Hace una funcion por cada billboard de la escena.
	// Es recomendable usarlo con moderacion.
	void forEachBillboards(function<void(GameBillboard&)> callback);

	// Libera memoria del juego.
	void release();
};