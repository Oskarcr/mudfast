#include "Game.h"

void Game::update() {

	Game::time = +deltaTime;

	int totalSeconds = (int)time;

	int uMinuto = time;
	int dMinuto = time;
	int uHora = time;
	int dHora = time;

	GameBillboard& minuteR = getBillboardById("minuteR");
	GameBillboard& minuteL = getBillboardById("minuteL");
	GameBillboard& hourR = getBillboardById("hourR");
	GameBillboard& hourL = getBillboardById("hourL");

	getBillboardById("minuteR").setAttribute("digitR", uMinuto);
	getBillboardById("minuteL").setAttribute("digitL", dMinuto);
	getBillboardById("hourR").setAttribute("digitR2", uHora);
	getBillboardById("hourL").setAttribute("digitL2", dHora);

	int minutes = totalSeconds / 60;
	int hours = minutes / 60;

	int minute_R = minutes % 10;
	int minute_L = (minutes / 10) % 10;

	int hour_R = hours % 10;
	int hour_L = (hours / 10) % 10;

	GameObject& carromoviendose = getObjectById("Car");

	float signo = carromoviendose.getAttribute("conducir") == 1 ? -1 : 1;
	Vector2 pos2d = carromoviendose.getPosition2D();
	pos2d.y += (0.4f * signo);
	carromoviendose.setPosition2D(pos2d);
	if (pos2d.y > 240) {
		carromoviendose.setAttribute("conducir", 1);
		carromoviendose.rotation.y += 180;
	}
	if (pos2d.y < -240) {
		carromoviendose.setAttribute("conducir", 0);
		carromoviendose.rotation.y -= 180;
	}

	//movimiento para billboards
	GameBillboard& person1 = getBillboardById("Per1");
	float signo2 = person1.getAttribute("andar") == 1 ? -1 : 1;
	Vector2 pos2d2 = person1.getPosition2D();
	pos2d2.y += (0.1f * signo2);
	person1.setPosition2D(pos2d2);
	if (pos2d2.y > -20) {
		person1.setAttribute("andar", 1);
	}
	if (pos2d2.y < -240) {
		person1.setAttribute("andar", 0);
	}
	GameBillboard& person2 = getBillboardById("Per2");
	float signo3 = person2.getAttribute("andar") == 1 ? -1 : 1;
	Vector2 pos3d2 = person2.getPosition2D();
	pos3d2.x += (0.05f * signo3);
	person2.setPosition2D(pos3d2);
	if (pos3d2.x > -50) {
		person2.setAttribute("andar", 1);
	}
	if (pos3d2.x < -150) {
		person2.setAttribute("andar", 0);
	}
	GameBillboard& person3 = getBillboardById("Per3");
	float signo4 = person3.getAttribute("andar") == 1 ? -1 : 1;
	Vector2 pos4d2 = person3.getPosition2D();
	pos4d2.x += (0.05f * signo4);
	person3.setPosition2D(pos4d2);
	if (pos4d2.x > 30) {
		person3.setAttribute("andar", 1);
	}
	if (pos4d2.x < 150) {
		person3.setAttribute("andar", 0);
	}




#pragma region Comentarios de pruebas
	//GameBillboard& bill = getBillboardById("myBill");
	//float signo = bill.getAttribute("regresa") == 1 ? -1 : 1;

	//

	//bill.size += 0.2f * signo;

	//if (bill.size > 5) {
	//	bill.setAttribute("regresa", 1);
	//}
	//if (bill.size < 1) {
	//	bill.setAttribute("regresa", 0);
	//}

	// Actualizamos la animacion cada 5 frames (NO SEGUNDOS)
	/*
	GameBillboard& bill = getBillboardById("myBill");
	float offsetY = bill.getAttribute("offsetY");
	if (offsetY > 1) {
		bill.nextFrame();
		bill.setAttribute("offsetY", 0);
	}
	else {
		bill.setAttribute("offsetY", offsetY + 1);
	}*/

	/*
	GameObject& obj = getObjectById("myObj");

	float signo = obj.getAttribute("regresa") == 1 ? -1 : 1;

	Vector2 pos2d = obj.getPosition2D();
	pos2d.x += (0.4f * signo);

	obj.setPosition2D(pos2d);

	if (pos2d.x > 80) {
		obj.setAttribute("regresa", 1);
	}
	if (pos2d.x < 0) {
		obj.setAttribute("regresa", 0);
	}*/

	/*
	// Obtenemos nuestra entidad
	GameBillboard& bill = getBillboardById("miBill");

	// Actualizamos la animacion cada 5 frames (NO SEGUNDOS)
	float offsetY = bill.getAttribute("offsetY");
	if (offsetY > 5) {
		bill.nextFrame();
		bill.setAttribute("offsetY", 0);
	}
	else {
		bill.setAttribute("offsetY", offsetY + 1);
	}*/
#pragma endregion

	

}