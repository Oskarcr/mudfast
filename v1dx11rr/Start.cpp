#include "Game.h"

void Game::start() {
	// Es como del void Start de unity

#pragma region BILLBOARDS
	//ÁRBOLES
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
	//lo pensé para decorar la casa o a donde hay que entregar los muebles y que se vea a quien le entregamos los muebles
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