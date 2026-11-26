//
//  Rect.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 08..
//

#pragma once

#include "../Vector2/Vector2.h"

namespace Engine {
struct Rect {
    Vector2 pos;
    float width;
    float height;

    Rect();
    Rect(float x, float y, float width, float height);
    Rect(Vector2 pos, float width, float height);

    float getWidth() const;
    float getHeight() const;

    float left() const;
    float right() const;
    float top() const;
    float bottom() const;
    Vector2 center() const;

    bool contains(Vector2 point) const;
    bool intersects(const Rect& other) const;

    const Vector2& getPos() const;
    float getX() const;
    float getY() const;

    Rect& setPos(float x, float y);
    Rect& setPos(Vector2 pos);
    Rect& setX(float x);
    Rect& setY(float y);

    Rect& setWidth(float width);
    Rect& setHeight(float height);
    Rect& setSize(float width, float height);
};
}
