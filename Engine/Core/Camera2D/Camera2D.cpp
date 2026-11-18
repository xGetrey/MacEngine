//
//  Camera2D.cpp
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 16..
//

#include "Camera2D.h"
#include <cmath>

namespace Engine {

Vector2 Camera2D::WorldToScreen(Vector2 position) const {
    float x = (position.x - target.x) * zoom;
    float y = (position.y - target.y) * zoom;
    
    float rad = rotation * static_cast<float>(M_PI) / 180.0f;
    float c = std::cos(rad);
    float s = std::sin(rad);
    float rx = x * c - y * s;
    float ry = x * s + y * c;
    
    return Vector2(rx + offset.x, ry + offset.y);
}

Vector2 Camera2D::ScreenToWorld(Vector2 position) const {
    if (zoom == 0.0f) return target;   // nullával nem osztunk

    // ugyanaz visszafelé, fordított sorrendben
    float x = position.x - offset.x;
    float y = position.y - offset.y;

    float rad = rotation * static_cast<float>(M_PI) / 180.0f;
    float c = std::cos(rad);
    float s = std::sin(rad);
    float rx =  x * c + y * s;   // visszaforgatás: a sin előjele fordul
    float ry = -x * s + y * c;

    return Vector2(rx / zoom + target.x, ry / zoom + target.y);
}

}
