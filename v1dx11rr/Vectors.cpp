#include "Vectors.h"

Vector2::Vector2() {}

Vector2::Vector2(float _x, float _y)
{
    x = _x;
    y = _y;
}

Vector2& Vector2::operator=(Vector2 vector)
{
    x = vector.x;
    y = vector.y;
    return *this;
}

Vector2& Vector2::operator=(float value)
{
    x = value;
    y = value;
    return *this;
}

Vector2 Vector2::operator+(float value)
{
    return Vector2(x + value, y + value);
}

Vector2 Vector2::operator+(Vector2 vector)
{
    return Vector2(x + vector.x, y + vector.y);
}

Vector2 Vector2::operator-(float value)
{
    return Vector2(x - value, y - value);
}

Vector2 Vector2::operator-(Vector2 vector)
{
    return Vector2(x - vector.x, y - vector.y);
}

Vector2 Vector2::operator*(float value)
{
    return Vector2(x * value, y * value);
}

Vector2 Vector2::operator*(Vector2 vector)
{
    return Vector2(x * vector.x, y * vector.y);
}

Vector2 Vector2::operator/(float value)
{
    return Vector2(x / value, y / value);
}

Vector2 Vector2::operator/(Vector2 vector)
{
    return Vector2(x / vector.x, y / vector.y);
}

float Vector2::magnitude() const
{
    return sqrtf(x * x + y * y);
}

Vector2 Vector2::pointOfDirection(float angle, float hypot)
{
    float radians = angle * PI / 180.0f;
    return Vector2(hypot * sin(radians), hypot * cos(radians));
}

float Vector2::dot(Vector2 vector) const {
    return x * vector.x + y * vector.y;
}

Vector2 Vector2::perp() const {
    return Vector2(-y, x);
}

Vector2 Vector2::normalize() const {
    float length = sqrtf(x * x + y * y);
    if (length == 0) return Vector2(0, 0);
    return Vector2(x / length, y / length);
}

string Vector2::toString() const
{
    return "(" + to_string(x) + "," + to_string(y) + ")";
}

Vector3::Vector3(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
}

Vector3& Vector3::operator=(Vector3 vector)
{
    x = vector.x;
    y = vector.y;
    z = vector.z;
    return *this;
}

Vector3& Vector3::operator=(float value)
{
    x = value;
    y = value;
    z = value;
    return *this;
}

Vector3 Vector3::operator+(float value)
{
    return Vector3(x + value, y + value, z + value);
}

Vector3 Vector3::operator+(Vector3 vector)
{
    return Vector3(x + vector.x, y + vector.y, z + vector.z);
}

Vector3 Vector3::operator-(float value)
{
    return Vector3(x - value, y - value, z - value);
}

Vector3 Vector3::operator-(Vector3 vector)
{
    return Vector3(x - vector.x, y - vector.y, z - vector.z);
}

Vector3 Vector3::operator*(float value)
{
    return Vector3(x * value, y * value, z * value);
}

Vector3 Vector3::operator*(Vector3 vector)
{
    return Vector3(x * vector.x, y * vector.y, z * vector.z);
}

Vector3 Vector3::operator/(float value)
{
    return Vector3(x / value, y / value, z / value);
}

Vector3 Vector3::operator/(Vector3 vector)
{
    return Vector3(x / vector.x, y / vector.y, z / vector.z);
}

float Vector3::magnitude() const
{
    return sqrtf(x * x + y * y + z * z);
}

Vector3 Vector3::cross(Vector3 vector) {
    Vector3 result;
    result.x = y * vector.z - z * vector.y;
    result.y = z * vector.x - x * vector.z;
    result.z = x * vector.y - y * vector.x;
    return result;
}

float Vector3::dot(Vector3 vector) {
    return x * vector.x + y * vector.y + z * vector.z;
}

Vector3 Vector3::rotateY(float angle) {
    float cosA = cos(angle * (PI / 180));
    float sinA = sin(angle * (PI / 180));
    return Vector3(
        x * cosA - z * sinA,
        y,
        x * sinA + z * cosA
    );
}

Vector3 Vector3::normalize() const {
    float length = magnitude();
    if (length == 0) return Vector3();
    return Vector3(x / length, y / length, z / length);
}

string Vector3::toString() const
{
    return "(" + to_string(x) + "," + to_string(y) + "," + to_string(z) + ")";
}