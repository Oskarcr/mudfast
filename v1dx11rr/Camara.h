#ifndef _camara
#define _camara
#include <string>

#define PI 3.1415f

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
		D3DXMatrixPerspectiveFovLH( &proyeccion, D3DX_PI/2.6f, ancho / alto, 0.08f, 1000.0f );
		//las transpone para acelerar la multiplicacion
		D3DXMatrixTranspose( &vista, &vista );
		D3DXMatrixTranspose( &proyeccion, &proyeccion );

		D3DXVec3Normalize(&refUp, &refUp);

		refFront = D3DXVECTOR3(target.x - eye.x, target.y - eye.y, target.z - eye.z);
		D3DXVec3Normalize(&refFront, &refFront);

		D3DXVec3Cross(&refRight, &refFront, &refUp);
		D3DXVec3Normalize(&refRight, &refRight);
		
	}


	D3DXMATRIX UpdateCam(float * fpos, float * frot, float * foff)
	{
		posCam.x = fpos[0];
		posCam.y = fpos[1] + 10.0f;
		posCam.z = fpos[2];

		/*D3DXVECTOR4 tempo;
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

		OutputDebugStringA(("(" + std::to_string(posCam.x) + "," + std::to_string(posCam.z) + ")\n").c_str());

		//actualizamos la matriz de vista
		D3DXVECTOR3 target = posCam + refFront;
		D3DXMatrixLookAtLH(&vista, &posCam, &target, &refUp);
		D3DXMatrixTranspose(&vista, &vista);*/

		// Ángulos de rotación absoluta (radianes)
		float yaw = frot[1] * (PI / 180.f); // izquierda/derecha
		float pitch = frot[0] * (PI / 180.f); // arriba/abajo
		float roll = 0.0f;    // generalmente 0 para tercera persona

		// Matriz de rotación desde yaw/pitch/roll
		D3DXMATRIX rotationMat;
		D3DXMatrixRotationYawPitchRoll(&rotationMat, yaw, pitch, roll);

		// Definir el vector offset
		D3DXVECTOR3 offset(foff[0], foff[1], foff[2]);

		// Aplicar la rotacion al offset
		D3DXVec3TransformCoord(&offset, &offset, &rotationMat);

		// Y sumarol
		posCam += offset;

		// Vector forward base
		D3DXVECTOR3 forward(0.0f, 0.0f, 1.0f);
		D3DXVec3TransformCoord(&refFront, &forward, &rotationMat);
		D3DXVec3Normalize(&refFront, &refFront);

		// Recalcular vector right
		D3DXVec3Cross(&refRight, &refFront, &refUp);
		D3DXVec3Normalize(&refRight, &refRight);

		// Target de la cámara
		D3DXVECTOR3 target = posCam + refFront;

		// Matriz de vista
		D3DXMatrixLookAtLH(&vista, &posCam, &target, &refUp);
		D3DXMatrixTranspose(&vista, &vista);
		return vista;
	}

	~Camara()
	{
	}
};
#endif