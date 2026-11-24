//
//  Rect.cpp
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 08..
//

#include "Rect.h"

namespace Engine {
Rect::Rect() : pos(0, 0), width(0), height(0) { }

Rect::Rect(float x, float y, float width, float height) : pos(x, y), width(width), height(height) { }

Rect::Rect(Vector2 pos, float width, float height) : pos(pos), width(width), height(height) { }

const Vector2& Rect::getPos() const {
    return pos;
}

float Rect::getX() const {
    return pos.x;
}

float Rect::getY() const {
    return pos.y;
}

float Rect::left() const {
    return pos.x;
}

float Rect::top() const {
    return pos.y;
}

Vector2 Rect::center() const {
    return Vector2(pos.x + width / 2, pos.y + height / 2);
}

float Rect::right() const {
    return pos.x + width;
}

float Rect::bottom() const {
    return pos.y + height;
}

float Rect::getWidth() const {
    return width;
}

float Rect::getHeight() const {
    return height;
}

Rect& Rect::setPos(Vector2 pos) {
    this->pos = pos;
    return *this;
}

Rect& Rect::setPos(float x, float y) {
    pos.x = x;
    pos.y = y;
    return *this;
}

Rect& Rect::setX(float x) {
    pos.x = x;
    return *this;
}

Rect& Rect::setY(float y) {
    pos.y = y;
    return *this;
}

Rect& Rect::setWidth(float width) {
    this->width = width;
    return *this;
}

Rect& Rect::setHeight(float height) {
    this->height = height;
    return *this;
}

Rect& Rect::setSize(float width, float height) {
    this->width = width;
    this->height = height;
    return *this;
}


/*
Rect& Rect::move(Vector2 velocity, float dt) {
    pos.x += velocity.x * dt;
    pos.y += velocity.y * dt;
    return *this;
}

Rect& Rect::move(float vx, float vy, float dt) {
    pos.x += vx * dt;
    pos.y += vy * dt;
    return *this;
}

Rect& Rect::moveX(float vx, float dt) {
    pos.x += vx * dt;
    return *this;
}

Rect& Rect::moveY(float vy, float dt) {
    pos.y += vy * dt;
    return *this;
}

Rect& Rect::moveTo(Vector2 target, float speed, float dt) {
    Vector2 toTarget = target - pos;
    float distance = toTarget.length();
    float step = speed * dt;
    
    if (distance <= step) {
        pos = target;
        return *this;
    }

    pos += toTarget * (step / distance);
    return *this;
}
*/

}
