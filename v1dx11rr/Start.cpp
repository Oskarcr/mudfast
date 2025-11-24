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



#pragma region BILLBOARDS
	//�RBOLES
	GameBillboard& bill = createBillboard("A1", A_1);
	GameBillboard& bill2 = createBillboard("A2", A_2);
	GameBillboard& bill3 = createBillboard("A3", A_3);
	GameBillboard& bill4 = createBillboard("A4", A_3);
	GameBillboard& bill5 = createBillboard("A5", A_2);
	GameBillboard& bill6 = createBillboard("A6", A_1);

	bill.setPosition2D(-48, -52);
	bill2.setPosition2D(-73, 68);
	bill3.setPosition2D(-92, -88);
	bill4.setPosition2D(-103, 72);
	bill5.setPosition2D(-109, -128);
	bill6.setPosition2D(-128, 147);

	bill.size = 10;
	bill2.size = 13;
	bill3.size = 15;
	bill4.size = 12;
	bill5.size = 14;
	bill6.size = 11;

	//PERSONAS
	//lo pens� para decorar la casa o a donde hay que entregar los muebles y que se vea a quien le entregamos los muebles
	GameBillboard& esposo = createBillboard("Esp", MARRIDO);
	GameBillboard& esposa = createBillboard("Espa", MARIDA);
	esposo.setPosition2D(20, 20);
	esposa.setPosition2D(25, 25);
	esposo.size = 3;
	esposa.size = 3;
#pragma endregion

#pragma region MODELOS

#pragma endregion




#pragma region COMENTARIOS DE PRUBAS
	//GameObject& myObj = createObject("myObj", OBJ_BOX_BIG);
	//myObj.setAttribute("regresa", 0);

	//GameBillboard& bill = createBillboard("myBill", BILL_CAT_CHAD);

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
#pragma endregion

	
	

}