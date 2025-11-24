#ifndef _camara
#define _camara

//Clase camara hecha por Rafael Rosas para los UltraLMADs
//Videojuegos

#include <d3d11.h>
#include <D3DX11.h>
#include <D3DX10math.h>

#include "Colision.h"
//#include "Animation.h"

class Camara{
public:
	D3DXVECTOR3 posCam;
	D3DXVECTOR3 hdveo;
	D3DXVECTOR3 hdvoy;
	D3DXVECTOR3 refUp;
	D3DXVECTOR3 refRight;
	D3DXVECTOR3 refFront;
	D3DXMATRIX vista;
	D3DXMATRIX proyeccion;
	int ancho;
	int alto;

	BoundingSphere getCollider(float radius = 1.0f) const {
		return BoundingSphere{ posCam, radius, "Camara" };
	}


	Camara(D3DXVECTOR3 eye, D3DXVECTOR3 target, D3DXVECTOR3 up, int Ancho, int Alto)
	{
		//posicion de la camara
		posCam = eye;
		//a donde ve
		hdveo = target;
		refUp = up;
		ancho = Ancho;
		alto = Alto;

		//crea la matriz de vista
		D3DXMatrixLookAtLH(&vista, &posCam, &hdveo, &refUp);
		//la de proyeccion
		D3DXMatrixPerspectiveFovLH( &proyeccion, D3DX_PI/4.0, ancho / alto, 0.01f, 1000.0f );
		//las transpone para acelerar la multiplicacion
		D3DXMatrixTranspose( &vista, &vista );
		D3DXMatrixTranspose( &proyeccion, &proyeccion );

		D3DXVec3Normalize(&refUp, &refUp);

		refFront = D3DXVECTOR3(target.x - eye.x, target.y - eye.y, target.z - eye.z);
		D3DXVec3Normalize(&refFront, &refFront);

		D3DXVec3Cross(&refRight, &refFront, &refUp);
		D3DXVec3Normalize(&refRight, &refRight);
		
	}


	D3DXMATRIX UpdateCam(float velFB, float velRL, float arriaba, float izqder)
	{
		D3DXVECTOR4 tempo;
		D3DXQUATERNION quatern;
		D3DXMATRIX giraUp, giraRight;

		//creamos al quaternion segun el vector up
		D3DXQuaternionRotationAxis(&quatern, &refUp, izqder);
		//lo normalizamos para que no acumule error
		D3DXQuaternionNormalize(&quatern, &quatern);
		//creamos la matriz de rotacion basados en el quaternion
		D3DXMatrixRotationQuaternion(&giraUp, &quatern);


		//transformamos a los vectores ded la camara
		D3DXVec3Transform(&tempo, &refFront, &giraUp);
		refFront = (D3DXVECTOR3)tempo;
		D3DXVec3Normalize(&refFront, &refFront);
		D3DXVec3Cross(&refRight, &refFront, &refUp);

		//una vez calculado right a partir de front y up ahora rotamos sobre right
		//repetimos el procedimiento anterior
		D3DXQuaternionRotationAxis(&quatern, &refRight, arriaba);
		D3DXQuaternionNormalize(&quatern, &quatern);
		D3DXMatrixRotationQuaternion(&giraRight, &quatern);

		D3DXVec3Transform(&tempo, &refFront, &giraRight);
		refFront = (D3DXVECTOR3)tempo;
		D3DXVec3Normalize(&refFront, &refFront);

		
		// Proyectamos refFront sobre el plano horizontal (y = 0)
		D3DXVECTOR3 forward = refFront;
		forward.y = 0; 
		D3DXVec3Normalize(&forward, &forward);

		posCam += forward * velFB / 10.0;
		posCam += refRight * velRL / 10.0;

		//ajustamos la matriz de vista con lo obtenido
		//////posCam += forward * velFB / 10.0;
		//////posCam += refRight * velRL / 10.0;
		/*
		posCam += forward * velFB / 10.0;
		posCam += refRight * velRL / 10.0;
				//collision
		D3DXVECTOR3 nextPos = posCam + forward * velFB / 10.0f + refRight * velRL / 10.0f;
		BoundingSphere nextCamCollider{ nextPos, 1.0f, "Camara" };
		
		bool colisiona = false;
		for (auto& pair : models) {
			AnimState& anim = pair.second;
			if (!anim.activa) continue;

			BoundingBox modelCollider{
				D3DXVECTOR3(anim.posX - 2.5f, anim.posY, anim.posZ - 2.5f),
				D3DXVECTOR3(anim.posX + 2.5f, anim.posY + 5.0f, anim.posZ + 2.5f),
				anim.name
			};
			
			if (::checkCollision(nextCamCollider, modelCollider)) {
				std::cout << "Colisión con " << anim.name << std::endl;
				colisiona = true;

				if (anim.name.find("Box") != std::string::npos && !anim.recogida) {
					anim.activa = false;
					anim.recogida = true;
					tienesCaja = true;
					std::cout << "Recogiste la caja: " << anim.name << std::endl;
				}
				break;
			}
		}
		if (!colisiona) {
			posCam = nextPos;
		}*/




		//actualizamos la matriz de vista
		D3DXVECTOR3 target = posCam + refFront;
		D3DXMatrixLookAtLH(&vista, &posCam, &target, &refUp);
		D3DXMatrixTranspose(&vista, &vista);
		return vista;
	}

	~Camara()
	{
	}
};
#endif