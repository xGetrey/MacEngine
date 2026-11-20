//
//  Vector2.cpp
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 28..
//

#include "Vector2.h"

namespace Engine {

Vector2::Vector2(float x, float y) : x(x), y(y) {}

bool Vector2::equal(const Vector2 other) const {
    return x == other.x && y == other.y;
}

bool Vector2::equalX(const Vector2 other) const {
    return x == other.x;
}

bool Vector2::equalY(const Vector2 other) const {
    return y == other.y;
}

void Vector2::set(float newX, float newY) {
    x = newX;
    y = newY;
}

Vector2 Vector2::copy() const {
    return Vector2(x, y);
}

//Aritmetikai
Vector2& Vector2::add(Vector2 other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2 Vector2::added(const Vector2 other) const {
    return Vector2(x + other.x, y + other.y);
}

Vector2& Vector2::subtract(const Vector2 other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2 Vector2::subtracted(const Vector2 other) const {
    return Vector2(x - other.x, y-other.y);
}

Vector2& Vector2::scale(const Vector2 other) {
    x *= other.x;
    y *= other.y;
    return *this;
}

Vector2 Vector2::scaled(const Vector2 other) const {
    return Vector2(x * other.x, y * other.y);
}

Vector2& Vector2::negate() {
    x = -x;
    y = -y;
    return *this;
}

Vector2 Vector2::negated() const {
    return Vector2(-x, -y);
}

Vector2& Vector2::divide(const Vector2 other) {
    x /= other.x;
    y /= other.y;
    return *this;
}

Vector2 Vector2::divided(const Vector2 other) const {
    return Vector2(x / other.x, y / other.y);
}

//operators
Vector2 Vector2::operator+(const Vector2 other) const {
    return added(other);
}

Vector2& Vector2::operator+=(const Vector2 other) {
    add(other);
    return *this;
}

Vector2 Vector2::operator-() const {
    return Vector2(-x, -y);
}

Vector2 Vector2::operator-(const Vector2 other) const {
    return subtracted(other);
}

Vector2& Vector2::operator-=(const Vector2 other) {
    return subtract(other);
}

Vector2 Vector2::operator*(const Vector2 other) const {
    return scaled(other);
}

Vector2& Vector2::operator*=(const Vector2 other) {
    return scale(other);
}

Vector2 Vector2::operator/(const Vector2 other) const {
    return divided(other);
}

Vector2& Vector2::operator/=(const Vector2 other) {
    return divide(other);
}

bool Vector2::operator==(const Vector2 other) const {
    return x == other.x && y == other.y;
}

//float
Vector2 Vector2::operator+(float value) const {
    return Vector2(x + value, y + value);
}

Vector2 Vector2::operator-(float value) const {
    return Vector2(x - value, y - value);
}

Vector2 Vector2::operator*(float value) const {
    return Vector2(x * value, y * value);
}

Vector2 Vector2::operator/(float value) const {
    return Vector2(x / value, y / value);
}


Vector2& Vector2::operator+=(float value) {
    x += value;
    y += value;
    return *this;
}

Vector2& Vector2::operator-=(float value) {
    x -= value;
    y -= value;
    return *this;
}

Vector2& Vector2::operator*=(float value) {
    x *= value;
    y *= value;
    return *this;
}

Vector2& Vector2::operator/=(float value) {
    x /= value;
    y /= value;
    return *this;
}


std::string Vector2::toString() const {
    return "x: " + std::to_string(x) + ", y: " + std::to_string(y);
}

Vector2 operator+(float value, Vector2 vector2) {
    return vector2.operator+(value);
}

Vector2 operator-(float value, Vector2 vector2) {
    return Vector2(value - vector2.x, value - vector2.y);
}

Vector2 operator*(float value, Vector2 vector2) {
    return vector2.operator*(value);
}

Vector2 operator/(float value, Vector2 vector2) {
    return Vector2(value / vector2.x, value / vector2.y);
}

}
