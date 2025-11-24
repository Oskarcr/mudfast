#pragma once
#include <d3dx10math.h>
#include <string>
#include <vector>
// #include "ModeloRR.h"
// #include "DXRR.h"

// Hola hola hola hola hola hola

struct BoundingSphere {
    D3DXVECTOR3 center;
    float radius;
    std::string name; // verificar el modelo
};
struct BoundingBox {
    D3DXVECTOR3 min; // esquina(x,y,z)
    D3DXVECTOR3 max; // esquina (x,y,z)
    std::string name;
};
inline bool checkCollision(const BoundingSphere& sphere, const BoundingBox& box) {
    float x = max(box.min.x, min(sphere.center.x, box.max.x));
    float y = max(box.min.y, min(sphere.center.y, box.max.y));
    float z = max(box.min.z, min(sphere.center.z, box.max.z));

    D3DXVECTOR3 closestPoint(x, y, z);
    D3DXVECTOR3 diff = sphere.center - closestPoint;
    float distSq = D3DXVec3LengthSq(&diff);
    return distSq <= (sphere.radius * sphere.radius);
}



// Hola - Oscar 22/11/2025

// Dibujar caja en modo wireframe usando las esquinas min/max
/*void DrawWireBox(const D3DXVECTOR3& min, const D3DXVECTOR3& max,
    const D3DXMATRIX& vista, const D3DXMATRIX& proyeccion,
    const D3DXVECTOR3& camPos, D3DXCOLOR color)
{
    // Definir 8 v�rtices de la caja
    D3DXVECTOR3 vertices[8] = {
        {min.x, min.y, min.z},
        {max.x, min.y, min.z},
        {max.x, max.y, min.z},
        {min.x, max.y, min.z},
        {min.x, min.y, max.z},
        {max.x, min.y, max.z},
        {max.x, max.y, max.z},
        {min.x, max.y, max.z}
    };

    // Definir 12 aristas (pares de �ndices)
    int edges[24] = {
        0,1, 1,2, 2,3, 3,0, // cara frontal
        4,5, 5,6, 6,7, 7,4, // cara trasera
        0,4, 1,5, 2,6, 3,7  // conexiones
    };
}
// Dibujar esfera en modo wireframe alrededor de un centro
void DrawWireSphere(const D3DXVECTOR3& center, float radius,
    const D3DXMATRIX& vista, const D3DXMATRIX& proyeccion,
    const D3DXVECTOR3& camPos, D3DXCOLOR color)
{
    const int slices = 16; //resoluci�n
    std::vector<D3DXVECTOR3> vertices;

    // Generar c�rculo en XY
    for (int i = 0; i < slices; i++) {
        float theta = (2.0f * D3DX_PI * i) / slices;
        vertices.push_back(D3DXVECTOR3(center.x + radius * cosf(theta),
            center.y + radius * sinf(theta),
            center.z));
    }

    // Generar c�rculo en XZ
    for (int i = 0; i < slices; i++) {
        float theta = (2.0f * D3DX_PI * i) / slices;
        vertices.push_back(D3DXVECTOR3(center.x + radius * cosf(theta),
            center.y,
            center.z + radius * sinf(theta)));
    }

    // Generar c�rculo en YZ
    for (int i = 0; i < slices; i++) {
        float theta = (2.0f * D3DX_PI * i) / slices;
        vertices.push_back(D3DXVECTOR3(center.x,
            center.y + radius * cosf(theta),
            center.z + radius * sinf(theta)));
    }
}*/