//
//  Rect.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 08..
//

#pragma once

#include "../Vector2/Vector2.h"
#include "../Time/Time.h"

namespace Engine {
struct Rect {
    // Szabadon írható adatok: rect.pos.x = 7.0f vagy rect.setX(7.0f), ahogy tetszik
    Vector2 pos;
    float width;
    float height;

    Rect();
    Rect(float x, float y, float width, float height);
    Rect(Vector2 pos, float width, float height);

    float getWidth() const;
    float getHeight() const;

    // Ezek mindig a pos/width/height alapján számolnak, így sosem lehetnek elavultak
    float getLeft() const;
    float getRight() const;
    float getTop() const;
    float getBottom() const;
    Vector2 getCenter() const;

    //Később majd megcsinálom
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

    Rect& move(Vector2 velocity, float dt = GetDeltaTime());
    Rect& move(float vx, float vy, float dt = GetDeltaTime());
    Rect& moveX(float vx, float dt = GetDeltaTime());
    Rect& moveY(float vy, float dt = GetDeltaTime());

    Rect& moveTo(Vector2 target, float speed, float dt = GetDeltaTime());
};
}
