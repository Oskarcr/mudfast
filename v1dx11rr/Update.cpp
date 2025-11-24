#include "Game.h"

void Game::update() {
	// Es como el void Update de unity

	
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