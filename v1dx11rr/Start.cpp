#include "Game.h"

void Game::start() {
	// Es como del void Start de unity

	GameObject& van = createObject("Van", OBJ_CAR_VAN);
	van.setPosition2D(30, -240);

	GameObject& car = createObject("Car", OBJ_CAR_DEFAULT);
	car.setPosition2D(-30, 240);

	GameObject& bigBox = createObject("BigBox", OBJ_BOX_BIG);
	bigBox.setPosition2D(30, -275);

	GameObject& midBox = createObject("MidBox", OBJ_BOX_MEDIUM);
	midBox.setPosition2D(30, -280);

	GameObject& smallBox = createObject("SmallBox", OBJ_BOX_SMALL);
	smallBox.setPosition2D(35, -280);

	GameObject& machine = createObject("VendingMachine", OBJ_COCA_COLA_VENDING);
	machine.setPosition2D(45, -280);

	GameObject& mattress = createObject("Mattress", OBJ_MATRESS);
	mattress.setPosition2D(50, -275);

	for (int i = 0; i < 20; i++) {
		GameObject& bush = createObject("Bush", OBJ_BUSH);
		float posX = (i < 10) ? -100 : -150;
		float posY = (i < 10) ? -200 : -500;
		bush.setPosition2D(posX, posY + (i * 35));
	}



	for(int i = 0; i < 6; i++) {
		GameObject& gasBomb = createObject("GasBomb" + to_string(i), OBJ_GAS_BOMB);
		float posX = (i < 3) ? 175 : 100;
		float posY = (i < 3) ? 25 : 0;
		gasBomb.setPosition2D(posX + (i * 25), posY);
	}



	//GameObject& myObj = createObject("myObj", OBJ_BOX_BIG);
	//myObj.setAttribute("regresa", 0);

	GameBillboard& bill = createBillboard("myBill", BILL_CAT_CHAD);

	// bill.setFrameData(4, 6, 24);
	/*
	createObject("miObj", OBJ_CAR_VAN);

	GameObject& obj = getObjectById("miObj");

	obj.setPosition2D(80, 0);
	*/
	/*
	GameBillboard& bill = createBillboard("miBill", BILL_FIRE);
	bill.setAttribute("offsetY", 0);
	bill.setPosition2D(80, 0);
	// La animacion
	bill.setFrameData(4, 8, 32);*/

}