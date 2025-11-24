#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <d3dx10math.h>
#include "TerrenoRR.h"
#include "Camara.h"
#include "SkyDome.h"
#include "Billboard.h"
#include "ModeloRR.h"
#include "XACT3Util.h"

//MIS RECURSOS
// #include "Colision.h"

#include "Vectors.h"

struct AnimState {
    float posX, posZ, posY;   // posición con respectivo al terreno
    float rotY;         // rotación
    float speedX;       // velocidad en X
    bool forward;       // dirección
    bool rotate;        // girar
    std::string name;   // nombre del modelo

    bool activa = true; // si está activo en la escena
    bool recogida = false; // si ya fue recogido
};

class AnimationManager {
public:
    void addModel(ModeloRR* model, AnimState state);
    void update();
    void apply(D3DXMATRIX vista, D3DXMATRIX proyeccion, D3DXVECTOR3 camPos);
    std::vector<std::pair<ModeloRR*, AnimState>>& getModels() {
        return models;
    }

	//objetos del jugador y victorias
    int getContadorObjetos() const {
        return contadorObjetos;
    }
    void setMeta(int m) { meta = m; }
    bool gano() const {
        return victoria;
    }

private:
    std::vector<std::pair<ModeloRR*, AnimState>> models;
	//contador de objetos recogidos
	int contadorObjetos = 0;
	int meta = 3; //objetos necesarios para ganar
	bool victoria = false;
};

inline void AnimationManager::addModel(ModeloRR* model, AnimState state) {
    models.push_back(std::make_pair(model, state));
}

inline void AnimationManager::update() {
    for (auto& pair : models) {
        AnimState& anim = pair.second;

        if (anim.name == "Car") {
            if (anim.forward) {
                anim.posX += anim.speedX;
                if (anim.posX > 100.0f) anim.forward = false;
                anim.rotY = D3DXToRadian(90);
            }
            else {
                anim.posX -= anim.speedX;
                if (anim.posX < 0.0f) anim.forward = true;
				anim.rotY = D3DXToRadian(-90);
            }
        }

        if (anim.name.find("Box") != std::string::npos && anim.rotate) {
            anim.rotY += 0.02f;
        }
    }
}

inline void AnimationManager::apply(D3DXMATRIX vista, D3DXMATRIX proyeccion, D3DXVECTOR3 camPos) 
{
    BoundingSphere camCollider{ camPos, 1.0f, "Camara" };
    //DrawWireSphere(camCollider.center, camCollider.radius, camara->vista, camara->proyeccion, camara->posCam, D3DXCOLOR(0, 1, 0, 1));

    for (auto& pair : models) {
        ModeloRR* model = pair.first;
        AnimState& anim = pair.second;

        if (!anim.activa) continue;

        BoundingBox modelCollider{
            D3DXVECTOR3(anim.posX - 2.5f, anim.posY, anim.posZ - 2.5f), // tmañao minuimo
            D3DXVECTOR3(anim.posX + 2.5f, anim.posY + 5.0f, anim.posZ + 2.5f), // tamaño máximo
            anim.name
        };

        if (::checkCollision(camCollider, modelCollider)) {
            if (anim.name.find("Box") != std::string::npos && !anim.recogida) {
                anim.activa = false;
                anim.recogida = true;
				contadorObjetos++;
                std::cout << "Recogiste la caja: " << anim.name << std::endl;
            } else if (anim.name.find("Car") !=  std::string::npos && contadorObjetos == 0) {
                //para la victoria
                victoria = true;
                std::cout << "¡Has ganado! ";
            }
        }
        /*
        model->Draw(
            vista,
            proyeccion,
            anim.posX,
            anim.posZ,
            anim.posY,
            camPos,
            10.0f,
            anim.rotY,
            'Y',
            1.0f,
            0.5f
        );*/

        //DrawWireBox(modelCollider.min, modelCollider.max, vista, proyeccion, camPos, D3DXCOLOR(1, 0, 0, 1));
    }
}