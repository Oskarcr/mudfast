#include "Game.h"



Game::Game() {
	previousTime = steady_clock::now();
}

Game::~Game() {

}

Vector2 Game::getMousePosition() {
	POINT cursor;
	GetCursorPos(&cursor);
	return Vector2(cursor.x, cursor.y);
}

Vector2 Game::saveMousePosition() {
	lastMousePosition = getMousePosition();
	return lastMousePosition;
}

Vector2 Game::getMouseDeltaPosition() {
	return lastMousePosition - getMousePosition();
}

Vector2 Game::getScreenSize() {
	return Vector2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
}

void Game::setMousePosition(Vector2 position) {
	SetCursorPos((int)position.x, (int)position.y);
}

void Game::setMousePosition(float x, float y) {
	return setMousePosition(Vector2(x, y));
}

GameObject& Game::createObject(string id, EntityType type) {
	while (hasObject(id)) id = id + "_c";

	string folderName = getAssetNameByEntityType(type);
	string pathModel = "Assets/" + folderName + "/" + folderName + ".obj";
	string pathColor = "Assets/" + folderName + "/" + folderName + "-color.png";

	const char* cPathModel = pathModel.c_str();
	wstring wPathColor(pathColor.begin(), pathColor.end());
	WCHAR* wcPathColor = (WCHAR*)wPathColor.c_str();

	ModeloRR* modelRR = new ModeloRR(
		game.d3dDevice,
		d3dContext,
		(char*)cPathModel,
		wcPathColor,
		L"Assets/noSpecMap.jpg",
		0, 
		0
	);

	GameObject* gameObject = new GameObject(modelRR);
	gameObject->setPosition(Vector3());
	objects[id] = gameObject;
	return getObjectById(id);
}

GameBillboard& Game::createBillboard(string id, EntityType type) {
	while (hasBillboard(id)) id = id + "_c";

	string folderName = getAssetNameByEntityType(type);
	string pathTexture = "Assets/Billboards/" + folderName + ".png";
	wstring wPathTexture(pathTexture.begin(), pathTexture.end());
	WCHAR* wcPathTexture = (WCHAR*)wPathTexture.c_str();
	BillboardRR *billboardRR = new BillboardRR(
		wcPathTexture,
		L"Assets/noNormMap.png",
		d3dDevice, 
		d3dContext, 
		5
	);
	GameBillboard* billboard = new GameBillboard(billboardRR);
	billboards[id] = billboard;
	return getBillboardById(id);
}

float Game::surface(Vector2 position) {
	return surface(position.x, position.y);
}

float Game::surface(float x, float y) {
	return land->Superficie(x, y);
}

void Game::setContext(ID3D11DeviceContext* _d3dContext) {
	d3dContext = _d3dContext;
}

void Game::setDevice(ID3D11Device* _d3dDevice) {
	d3dDevice = _d3dDevice;
}

void Game::setCamera(Camara* _camera) {
	camera = GameCamera(_camera, land);
}

void Game::setLand(TerrenoRR * _land) {
	land = _land;
}

TerrenoRR* Game::getLand() {
	return land;
}

void Game::render() {
	setMousePosition(Vector2(game.getScreenSize().x / 2, game.getMousePosition().y));
	saveMousePosition();
	camera.render();
	updateTime();
	// No se toca, solo sera para renderizar
	forEachObjects([](GameObject& gameObject) {
		gameObject.render();
	});
	forEachBillboards([](GameBillboard& billboard) {
		billboard.render();
	});
}

void Game::updateTime() {
	currentTime = steady_clock::now();
	duration<float> delta = currentTime - previousTime;
	deltaTime = delta.count();
	time += deltaTime;
	previousTime = currentTime;
}

GameObject& Game::getObjectById(string id) {
	return *objects[id];
}

bool Game::hasObject(string id) {
	return objects.find(id) != objects.end();
}

GameBillboard& Game::getBillboardById(string id) {
	return *billboards[id];
}

bool Game::hasBillboard(string id) {
	return billboards.find(id) != billboards.end();
}

string Game::getAssetNameByEntityType(EntityType type) {
	string result = "";
	// Switch gigante para elegir que nombre es especificamente
	switch (type)
	{
	case OBJ_CAR_DEFAULT:
		result = "Car";
		break;
	case OBJ_POLICE_CAR:
		result = "Police";
		break;
	case OBJ_CAR_VAN:
		result = "Van";
		break;
	case OBJ_BOX_SMALL:
		result = "BoxS";
		break;
	case OBJ_BOX_MEDIUM:
		result = "BoxM";
		break;
	case OBJ_BOX_BIG:
		result = "BoxB";
		break;
	case OBJ_COCA_COLA_VENDING:
		result = "FridgeCocaCola";
		break;
	case OBJ_MATRESS:
		result = "Mattress";
		break;
	case OBJ_BUSH:
		result = "Bush";
		break;
	case OBJ_SOFA:
		result = "Sofa";
		break;
	case OBJ_TABLE:
		result = "DiningTable";
		break;
	case OBJ_GAS_BOMB:
		result = "GasBomb";
		break;
	case BILL_OBJETIVE:
		result = "Objetivo";
		break;
	case BILL_FIRE:
		result = "fuego-anim";
		break;
	case BILL_EXPLOSION:
		result = "Explo";
		break;
	case BILL_CAT_CHAD:
		result = "gato_chad";
		break;
	case A_1:
		result = "tree1";
		break;
	case A_2:
		result = "tree2";
		break;
	case A_3:
		result = "tree3";
		break;
	case BILL_BUSH:
		result = "Bush";
		break;
	case MARRIDO:
		result = "Husband";
		break;
	case MARIDA:
		result = "Sabrina";
		break;
	case CASA_1: //CASA
		result = "House1";
		break;
	case CASA_2:
		result = "unknown_Base_Color";
		break;
	case DEAD_SIG:
		result = "lambert1_Base_color";
		break;
	case STREET_L:
		result = "streetlight";
		break;
	case ALMACEN_1:
		result = "Warehouse_2_DefaultMaterial_AlbedoTranspar";
		break;
	case ALMACEN_2:
		result = "timage01";
		break;
	case EXPLORABLE_1:
		result = "Warehouse_Warehouse_AlbedoTransparency";
		break;
	case SHOP_1:
		result = "sklep-wizualiacja";
		break;
	case N_1:
		result = "1";
		break;
	case N_2:
		result = "2";
		break;
	case N_3:
		result = "3";
		break;
	case N_4:
		result = "4";
		break;
	case N_5:
		result = "5";
		break;
	case N_6:
		result = "6";
		break;
	case N_7:
		result = "7";
		break;
	case N_8:
		result = "8";
		break;
	case N_9:
		result = "9";
		break;
	case N_0:
		result = "0";
		break;
	}	
	return result;
}

void Game::forEachObjects(function<void(GameObject&)> callback) {
	for (auto &pair : objects) {
		callback(*pair.second);
	}
};

void Game::forEachBillboards(function<void(GameBillboard&)> callback) {
	for (auto& pair : billboards) {
		callback(*pair.second);
	}
};

void Game::release() {
	// Limpiar objetos
	for (auto& pair : objects) {
		delete pair.second; 
	}
	objects.clear();
	// Limpiar billboards
	for (auto& pair : billboards) {
		delete pair.second;
	}
	billboards.clear();
}