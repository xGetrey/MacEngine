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
    
    Vector2 operator+(const Vector2 other) const;
    Vector2 operator-(const Vector2 other) const;
    Vector2 operator*(const Vector2 other) const;
    Vector2 operator/(const Vector2 other) const;
    Vector2 operator-() const;
    
    Vector2& operator+=(const Vector2 other);
    Vector2& operator-=(const Vector2 other);
    Vector2& operator*=(const Vector2 other);
    Vector2& operator/=(const Vector2 other);
    
    Vector2 operator+(float value) const;
    Vector2 operator-(float value) const;
    Vector2 operator*(float value) const;
    Vector2 operator/(float value) const;
    
    Vector2& operator+=(float value);
    Vector2& operator-=(float value);
    Vector2& operator*=(float value);
    Vector2& operator/=(float value);
    
    Vector2() : x(0.0f), y(0.0f) {}
    Vector2(float x, float y);
    
    bool equal(const Vector2 other) const;
    bool equalX(const Vector2 other) const;
    bool equalY(const Vector2 other) const;
    
    void set(float x, float y);
    Vector2 copy() const;
    std::string toString() const;
    
    //Aritmetikai
    Vector2& add(const Vector2 other);
    Vector2& subtract(const Vector2 other);
    Vector2& scale(const Vector2 other);
    Vector2& divide(const Vector2 other);
    Vector2& negate();
    
    [[nodiscard]] Vector2 added(const Vector2 other) const;
    [[nodiscard]] Vector2 subtracted(const Vector2 other) const;
    [[nodiscard]] Vector2 scaled(const Vector2 other) const;
    [[nodiscard]] Vector2 divided(const Vector2 other) const;
    [[nodiscard]] Vector2 negated() const;
    
    [[nodiscard]] float length() const;
    [[nodiscard]] float squaredLength() const;
    [[nodiscard]] float distance(const Vector2 other) const;
    [[nodiscard]] float squaredDistance(const Vector2 other) const;
    [[nodiscard]] Vector2 normalized() const;
    [[nodiscard]] float dot(const Vector2 other) const;
    [[nodiscard]] float cross(const Vector2 other) const;
    Vector2& normalize();

    [[nodiscard]] Vector2 lerp(const Vector2 other, float t) const;
    [[nodiscard]] Vector2 perpendicular() const;
    [[nodiscard]] Vector2 rotated(float degrees) const;
    Vector2& rotate(float degrees);
    [[nodiscard]] float angle() const;
};

Vector2 operator+(float value, Vector2 vector2);
Vector2 operator-(float value, Vector2 vector2);
Vector2 operator*(float value, Vector2 vector2);
Vector2 operator/(float value, Vector2 vector2);

}
