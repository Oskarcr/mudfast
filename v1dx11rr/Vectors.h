#pragma once

#include <Windows.h>
#include <math.h>
#include <iostream>
#include <string>

#define PI 3.1415f

using namespace std;

/* Clases para los vectores de ambos tipos. */
class Vector2 {
public:
    float x = 0;
    float y = 0;

    Vector2();

    Vector2(float _x, float _y);

    Vector2& operator=(Vector2 vector);

    Vector2& operator=(float value);

    Vector2 operator+(float value);

    Vector2 operator+(Vector2 vector);

    Vector2 operator-(float value);

    Vector2 operator-(Vector2 vector);

    Vector2 operator*(float value);

    Vector2 operator*(Vector2 vector);

    Vector2 operator/(float value);

    Vector2 operator/(Vector2 vector);

    // Obtiene la magnitud del vector.
    float magnitude() const;

    // Obtiene la posicion de X y Y de un angulo con la hipotenusa.
    static Vector2 pointOfDirection(float angle, float hypot);

    // Devuelve la suma de los productos de cada componente.
    float dot(Vector2 vector) const;

    // Devuelve la perspectiva del vector.
    Vector2 perp() const;

    // Devuelve otro vector en base al vector objetivo con magnitud 1.
    Vector2 normalize() const;

    // Equivalente a "(" + to_string(x) + "," + to_string(y) + ")".
    string toString() const;
};

class Vector3 {
public:
    float x = 0;
    float y = 0;
    float z = 0;

    Vector3(float _x = 0, float _y = 0, float _z = 0);

    Vector3& operator =(Vector3 vector);

    Vector3& operator =(float value);

    Vector3 operator+(float value);

    Vector3 operator+(Vector3 vector);

    Vector3 operator-(float value);

    Vector3 operator-(Vector3 vector);

    Vector3 operator*(float value);

    Vector3 operator*(Vector3 vector);

    Vector3 operator/(float value);

    Vector3 operator/(Vector3 vector);

    // Obtiene la magnitud del vector.
    float magnitude() const;

    // Retorna un vector perpendicular a los vectores. 
    // Siendo el vectorA this y vectorB el vector colocado.
    Vector3 cross(Vector3 vector);

    // Devuelve la suma de los productos de cada componente.
    float dot(Vector3 vector);

    // Rota el punto en el eje Y.
    Vector3 rotateY(float angle);

    // Devuelve otro vector en base al vector objetivo con magnitud 1.
    Vector3 normalize() const;

    // Equivalente a "(" + to_string(x) + "," + to_string(y) + "," + to_string(z) + ")".
    string toString() const;
};