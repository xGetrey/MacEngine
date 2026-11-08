//
//  Rect.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 08..
//

#pragma once

#include "../Vector2.h"

namespace Engine {
struct Rect {
    Vector2 pos;
    float width;
    float height;

    Rect();
    Rect(float x, float y, float width, float height);
    Rect(Vector2 pos, float width, float height);

    float Left() const;
    float Right() const;
    float Top() const;
    float Bottom() const;
    Vector2 Center() const;

    //Később majd megcsinálom
    bool Contains(Vector2 point) const;
    bool Intersects(const Rect& other) const;
};
}
