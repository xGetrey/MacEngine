//
//  Camera2D.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 16..
//

#pragma once

#include "../Vector2.h"

namespace Engine {

struct Camera2D {
    Vector2 target;
    Vector2 offset;
    float rotation = 0.0f;
    float zoom = 1.0f;
    
    Vector2 WorldToScreen(Vector2 position) const;
    Vector2 ScreenToWorld(Vector2 position) const;
};

}
