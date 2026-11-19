//
//  Vector2D.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 28..
//

#pragma once

#include <string>

namespace Engine {
struct Vector2 {
    float x;
    float y;
    
    Vector2 operator+(const Vector2& position);
    
    Vector2() : x(0.0f), y(0.0f) {}
    Vector2(float x, float y);
    
    bool equal(const Vector2 position) const;
    bool equalX(const Vector2 position) const;
    bool equalY(const Vector2 position) const;
    
    void set(float x, float y);
    Vector2 copy() const;
    std::string toString() const;
    
    //Aritmetikai
    void add(const Vector2 position);
    Vector2 added(const Vector2 position) const;
};
}
