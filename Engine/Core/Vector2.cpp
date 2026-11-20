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

Vector2& Vector2::negate() {
    x = -x;
    y = -y;
    return *this;
}

Vector2 Vector2::negated() const {
    return Vector2(-x, -y);
}

//operators
Vector2 Vector2::operator+(const Vector2 other) const {
    return added(other);
}

Vector2 Vector2::operator-() const {
    return Vector2(-x, -y);
}


Vector2& Vector2::operator+=(const Vector2 other) {
    add(other);
    return *this;
}

Vector2 Vector2::operator-(const Vector2 other) const {
    return subtracted(other);
}

Vector2& Vector2::operator-=(const Vector2 other) {
    return subtract(other);
}

std::string Vector2::toString() const {
    return "x: " + std::to_string(x) + ", y: " + std::to_string(y);
}

}
