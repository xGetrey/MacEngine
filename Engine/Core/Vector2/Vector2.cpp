//
//  Vector2.cpp
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 28..
//

#include "Vector2.h"
#include <cmath>

namespace Engine {

Vector2::Vector2(float x, float y) : x(x), y(y) {}

bool Vector2::equal(const Vector2 other) const {
    return x == other.x && y == other.y;
}

bool Vector2::equalX(const Vector2 other) const {
    return x == other.x;
}

bool Vector2::equalY(const Vector2 other) const {
    return y == other.y;
}

void Vector2::set(float newX, float newY) {
    x = newX;
    y = newY;
}

Vector2 Vector2::copy() const {
    return Vector2(x, y);
}

Vector2& Vector2::add(Vector2 other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2 Vector2::added(const Vector2 other) const {
    return Vector2(x + other.x, y + other.y);
}

Vector2& Vector2::subtract(const Vector2 other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2 Vector2::subtracted(const Vector2 other) const {
    return Vector2(x - other.x, y-other.y);
}

Vector2& Vector2::scale(const Vector2 other) {
    x *= other.x;
    y *= other.y;
    return *this;
}

Vector2 Vector2::scaled(const Vector2 other) const {
    return Vector2(x * other.x, y * other.y);
}

Vector2& Vector2::negate() {
    x = -x;
    y = -y;
    return *this;
}

Vector2 Vector2::negated() const {
    return Vector2(-x, -y);
}

Vector2& Vector2::divide(const Vector2 other) {
    x /= other.x;
    y /= other.y;
    return *this;
}

Vector2 Vector2::divided(const Vector2 other) const {
    return Vector2(x / other.x, y / other.y);
}

Vector2 Vector2::operator+(const Vector2 other) const {
    return added(other);
}

Vector2& Vector2::operator+=(const Vector2 other) {
    add(other);
    return *this;
}

Vector2 Vector2::operator-() const {
    return Vector2(-x, -y);
}

Vector2 Vector2::operator-(const Vector2 other) const {
    return subtracted(other);
}

Vector2& Vector2::operator-=(const Vector2 other) {
    return subtract(other);
}

Vector2 Vector2::operator*(const Vector2 other) const {
    return scaled(other);
}

Vector2& Vector2::operator*=(const Vector2 other) {
    return scale(other);
}

Vector2 Vector2::operator/(const Vector2 other) const {
    return divided(other);
}

Vector2& Vector2::operator/=(const Vector2 other) {
    return divide(other);
}

Vector2 Vector2::operator+(float value) const {
    return Vector2(x + value, y + value);
}

Vector2 Vector2::operator-(float value) const {
    return Vector2(x - value, y - value);
}

Vector2 Vector2::operator*(float value) const {
    return Vector2(x * value, y * value);
}

Vector2 Vector2::operator/(float value) const {
    return Vector2(x / value, y / value);
}


Vector2& Vector2::operator+=(float value) {
    x += value;
    y += value;
    return *this;
}

Vector2& Vector2::operator-=(float value) {
    x -= value;
    y -= value;
    return *this;
}

Vector2& Vector2::operator*=(float value) {
    x *= value;
    y *= value;
    return *this;
}

Vector2& Vector2::operator/=(float value) {
    x /= value;
    y /= value;
    return *this;
}


std::string Vector2::toString() const {
    return "x: " + std::to_string(x) + ", y: " + std::to_string(y);
}

Vector2 operator+(float value, Vector2 vector2) {
    return vector2.operator+(value);
}

Vector2 operator-(float value, Vector2 vector2) {
    return Vector2(value - vector2.x, value - vector2.y);
}

Vector2 operator*(float value, Vector2 vector2) {
    return vector2.operator*(value);
}

Vector2 operator/(float value, Vector2 vector2) {
    return Vector2(value / vector2.x, value / vector2.y);
}

float Vector2::squaredLength() const {
    return x * x + y * y;
}

float Vector2::length() const {
    return std::sqrt(squaredLength());
}

float Vector2::distance(const Vector2 other) const {
    return (other - *this).length();
}

float Vector2::squaredDistance(const Vector2 other) const {
    return (other - *this).squaredLength();
}

Vector2 Vector2::normalized() const {
    const float len = length();
    if (len > 0.0f) {
        const float invLen = 1 / len;
        return {x * invLen, y * invLen};
    }
    return {0.0f, 0.0f};
}

Vector2& Vector2::normalize() {
    *this = normalized();
    return *this;
}

float Vector2::dot(const Vector2 other) const {
    return x * other.x + y * other.y;
}

float Vector2::cross(const Vector2 other) const {
    return x * other.y - y * other.x;
}

Vector2 Vector2::lerp(const Vector2 other, float t) const {
    return *this + (other - *this) * t;
}

Vector2 Vector2::perpendicular() const {
    return Vector2(-y, x);
}

Vector2 Vector2::rotated(float degrees) const {
    const float rad = degrees * static_cast<float>(M_PI) / 180.0f;
    const float c = std::cos(rad);
    const float s = std::sin(rad);
    return Vector2(x * c - y * s, x * s + y * c);
}

Vector2& Vector2::rotate(float degrees) {
    *this = rotated(degrees);
    return *this;
}

float Vector2::angle() const {
    return std::atan2(y, x) * 180.0f / static_cast<float>(M_PI);
}

}
