#include "Game.h"

void Game::start() {
	// Es como del void Start de unity

#pragma region MODELOS
	GameObject& van = createObject("Van", OBJ_CAR_VAN);
	van.setPosition2D(30, -240);

	GameObject& car = createObject("Car", OBJ_CAR_DEFAULT);
	car.setPosition2D(-20, 240);

	GameObject& policeCar = createObject("PoliceCar", OBJ_POLICE_CAR);
	policeCar.setPosition2D(-30, 0);

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
		GameObject& bush = createObject("Bush" + to_string(i), OBJ_BUSH);
		float posX = (i < 10) ? -100 : -150;
		float posY = (i < 10) ? -200 : -500;
		bush.setPosition2D(posX, posY + (i * 35));
	}

	for (int i = 0; i < 6; i++) {
		GameObject& gasBomb = createObject("GasBomb" + to_string(i), OBJ_GAS_BOMB);
		float posX = (i < 3) ? 175 : 100;
		float posY = (i < 3) ? 25 : 0;
		gasBomb.setPosition2D(posX + (i * 25), posY);
	}



	//CASAS 
	GameObject& caas = createObject("Casa", CASA_1);
	caas.setPosition2D(100, 60);
	caas.scale = Vector3(3, 3, 3);
	caas.rotation = Vector3(0, 90, 0);
	GameObject& caas2 = createObject("Casa3", CASA_3);
	caas2.setPosition2D(130, -50);
	caas2.scale = Vector3(0.03, 0.03, 0.03);
	GameObject& caas1 = createObject("Casa2", CASA_2);
	caas1.setPosition2D(50, 70);
	caas1.scale = Vector3(1.5, 1.5, .5);
	caas1.rotation = Vector3(0, 90, 0);



	//TIONDA
	GameObject& tiend = createObject("GasShop", SHOP_1);
	tiend.setPosition2D(170, 60);
	tiend.scale = Vector3(3, 3, 3);
	tiend.rotation = Vector3(0, 90, 0);



	//ALMACENES
	GameObject& alma2 = createObject("Almacen2", ALMACEN_2);
	alma2.setPosition2D(170, -50);
	alma2.scale = Vector3(3, 3, 3);
	GameObject& alma = createObject("Almacen1", ALMACEN_1);
	alma.setPosition2D(-220, 200);
	alma.scale = Vector3(7, 5, 7);



	//EXPLORABLE
	GameObject& explo = createObject("Explorable1", EXPLORABLE_1); 
	explo.setPosition2D(200, -200);
	explo.scale = Vector3(5, 5, 5);
	explo.rotation = Vector3(0, 180, 0);
	GameObject& explo2 = createObject("Explorable2", EXPLORABLE_2);
	explo2.setPosition2D(-50, 0);
	explo2.scale = Vector3(0.5, 0.5, 0.5);

	//señales de tráfico y cosas de la calle
	GameObject& sinal1 = createObject("Deadend", DEAD_SIG);	//no sé si deberíamos poner ids distintos, por si acaso lo dejé igual
	sinal1.setPosition2D(30, 200);
	sinal1.scale = Vector3(3, 6, 3);
	sinal1.rotation = Vector3(0, 180, 0);
	GameObject& sinal2 = createObject("Deadend", DEAD_SIG);
	sinal2.setPosition2D(30, -250);
	sinal2.scale = Vector3(3, 6, 3);
	sinal2.rotation = Vector3(0, 0, 0);
	GameObject& sinal3 = createObject("Deadend", DEAD_SIG);
	sinal3.setPosition2D(200, -80);
	sinal3.scale = Vector3(3, 6, 3);
	sinal3.rotation = Vector3(0, -90, 0);

	//LUCES DE LA CALLE
	//GameObject& luz = createObject("luzcalle", STREET_L);
	for (int i = 0; i < 7; i++) {
		GameObject& luz = createObject("luzcalle" + to_string(i), STREET_L);
		luz.setPosition2D(-30, -240 + (i * 75));
		luz.scale = Vector3(2, 4, 2);
	}
	//luz.setPosition2D(-30, 0);
	//luz.scale = Vector3(2, 4, 2);


#pragma endregion

#pragma region BILLBOARDS
	//ARBOLES
	GameBillboard& bill = createBillboard("A1", A_1);
	GameBillboard& bill2 = createBillboard("A2", A_2);
	GameBillboard& bill3 = createBillboard("A3", A_3);
	GameBillboard& bill4 = createBillboard("A4", A_3);
	GameBillboard& bill5 = createBillboard("A5", A_2);
	GameBillboard& bill6 = createBillboard("A6", A_1);

	GameBillboard& bill7 = createBillboard("A7", A_1);
	GameBillboard& bill8 = createBillboard("A8", A_2);
	GameBillboard& bill9 = createBillboard("A9", A_3);
	GameBillboard& bill10 = createBillboard("A10", A_3);
	GameBillboard& bill11 = createBillboard("A11", A_2);
	GameBillboard& bill12 = createBillboard("A12", A_1);

	//ARBUSTOS
	GameBillboard& bush = createBillboard("Bush", BILL_BUSH);
	GameBillboard& bush2 = createBillboard("Bush2", BILL_BUSH);
	GameBillboard& bush3 = createBillboard("Bush3", BILL_BUSH);
	GameBillboard& bush4 = createBillboard("Bush4", BILL_BUSH);
	GameBillboard& bush5 = createBillboard("Bush5", BILL_BUSH);
	GameBillboard& bush6 = createBillboard("Bush6", BILL_BUSH);


	bill.setPosition2D(-48, -52);
	bill2.setPosition2D(-73, 68);
	bill3.setPosition2D(-92, -88);
	bill4.setPosition2D(-103, 72);
	bill5.setPosition2D(-109, -128);
	bill6.setPosition2D(-128, 147);

	bill7.setPosition2D(80, -52);
	bill8.setPosition2D(80, 68);
	bill9.setPosition2D(50, -88);
	bill10.setPosition2D(150, 150);
	bill11.setPosition2D(80, -128);
	bill12.setPosition2D(80, 200);

	bill.size = 10;
	bill2.size = 13;
	bill3.size = 15;
	bill4.size = 12;
	bill5.size = 14;
	bill6.size = 11;

	bill7.size = 10;
	bill8.size = 13;
	bill9.size = 15;
	bill10.size = 12;
	bill11.size = 14;
	bill12.size = 11;

	bush.setPosition2D(180, 250);
	bush2.setPosition2D(60, 200);
	bush3.setPosition2D(80, 150);
	bush4.setPosition2D(180, 180);
	bush5.setPosition2D(100, -75);
	bush6.setPosition2D(150, 125);

	bush.size = 2;
	bush2.size = 2;
	bush3.size = 2;
	bush4.size = 2;
	bush5.size = 2;
	bush6.size = 2;


	//PERSONAS
	//lo pens� para decorar la casa o a donde hay que entregar los muebles y que se vea a quien le entregamos los muebles
	GameBillboard& esposo = createBillboard("Esp", MARRIDO);
	GameBillboard& esposa = createBillboard("Espa", MARIDA);
	esposo.setPosition2D(130, -10);
	esposa.setPosition2D(130, -15);
	esposo.size = 3;
	esposa.size = 3;

	//personas que busco animar
	GameBillboard& persona1 = createBillboard("Per1", PERSONA1);
	GameBillboard& persona2 = createBillboard("Per2", PERSONA2);
	GameBillboard& persona3 = createBillboard("Per3", PERSONA3);
	GameBillboard& persona4 = createBillboard("Per4", PERSONA4);
	persona1.setPosition2D(30, -240);
	persona2.setPosition2D(-50, 240);
	persona3.setPosition2D(30, 50);
	persona4.setPosition2D(-30, 15);
	persona1.size = 3;
	persona2.size = 3;
	persona3.size = 3;
	persona4.size = 3;
#pragma endregion

#pragma region UI
	// Timer;

	GameBillboard& minuteR = createBillboard("minuteR", N_0);
	GameBillboard& minuteL = createBillboard("minuteL", N_0);
	GameBillboard& hourR = createBillboard("hourR", N_7);
	GameBillboard& hourL = createBillboard("hourL", N_0);
	minuteR.setAttribute("time", 0);

	minuteR.setPosition(0, 0, 20);
	minuteL.setPosition(-4, 0, 20);
	hourR.setPosition(-8, 0, 20);
	hourL.setPosition(-12, 0, 20);





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