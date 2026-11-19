//
//  Vector2.cpp
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 28..
//

#include "Vector2.h"

namespace Engine {

Vector2::Vector2(float x, float y) : x(x), y(y) {}

bool Vector2::equal(const Vector2 position) const {
    return x == position.x && y == position.y;
}

bool Vector2::equalX(const Vector2 position) const {
    return x == position.x;
}

bool Vector2::equalY(const Vector2 position) const {
    return y == position.y;
}

void Vector2::set(float newX, float newY) {
    x = newX;
    y = newY;
}

Vector2 Vector2::copy() const {
    return Vector2(x, y);
}

//Aritmetikai
void Vector2::add(Vector2 position) {
    x += position.x;
    y += position.y;
}

Vector2 Vector2::added(const Vector2 position) const {
    return Vector2(x + position.x, y + position.y);
}

Vector2 Vector2::operator+(const Vector2 &position) {
    return added(position);
}



std::string Vector2::toString() const {
    return "x: " + std::to_string(x) + ", y: " + std::to_string(y);
}

}
