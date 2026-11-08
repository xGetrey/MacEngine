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

float Rect::Left() const {
    return pos.x;
}

float Rect::Right() const {
    return pos.x + width;
}

float Rect::Top() const {
    return pos.y;
}

float Rect::Bottom() const {
    return pos.y + height;
}

Vector2 Rect::Center() const {
    return Vector2(pos.x + width / 2, pos.y + height / 2);
}

}
