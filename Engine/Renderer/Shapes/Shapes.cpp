//
//  Shapes.cpp
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 13..
//

#include "Shapes.h"
#include "../Batch/RenderBatch.h"

#include <cmath>

namespace Engine {

void DrawRect(const Rect& rect, const Color& color) {
    Vector2 tl(rect.Left(), rect.Top());
    Vector2 tr(rect.Right(), rect.Top());
    Vector2 bl(rect.Left(), rect.Bottom());
    Vector2 br(rect.Right(), rect.Bottom());

    Internal::Vertex* v = Internal::Batch_Allocate(6);
    v[0] = {tl, color};
    v[1] = {tr, color};
    v[2] = {bl, color};

    v[3] = {tr, color};
    v[4] = {br, color};
    v[5] = {bl, color};
}

void DrawRectLines(const Rect& rect, const Color& color, const int thickness) {
    if (thickness == 0) {
        return;
    }

    float t = static_cast<float>(thickness);

    if (t * 2 >= rect.width || t * 2 >= rect.height) {
        DrawRect(rect, color);
        return;
    }

    float x = rect.Left(), y = rect.Top();
    float w = rect.width, h = rect.height;

    DrawRect(Rect(x, y, w, t), color);
    DrawRect(Rect(x, y + h - t, w, t), color);
    DrawRect(Rect(x, y + t, t, h  - 2 * t), color);
    DrawRect(Rect(x + w - t, y + t, t, h - 2 * t), color);
}

void DrawCircle(const Vector2 center, const float radius, const Color& color) {
    if (radius == 0) return;

    int segments = 8;
    if (radius > 0.25f) {
        segments = (int)std::ceil(M_PI / std::acos(1.0f - 0.25f / radius));
    }
    if (segments < 8) segments = 8;

    float step = 2.0f * M_PI / segments;

    // Az összes szelet helye egyszerre, egyetlen foglalással
    Internal::Vertex* v = Internal::Batch_Allocate(segments * 3);

    for (int i = 0; i < segments; i++) {
        float a0 = i * step;
        float a1 = (i + 1) * step;

        Vector2 p0(center.x + std::cos(a0) * radius, center.y + std::sin(a0) * radius);
        Vector2 p1(center.x + std::cos(a1) * radius, center.y + std::sin(a1) * radius);

        v[i * 3 + 0] = {center, color};
        v[i * 3 + 1] = {p0, color};
        v[i * 3 + 2] = {p1, color};
    }
}

void DrawSemicircle(const Vector2 center, const float radius, const float rotate, const Color& color) {
    if (radius <= 0) return;

    int segments = 8;
    if (radius > 0.25f) {
        segments = (int)std::ceil(M_PI / std::acos(1.0f - 0.25f / radius));
    }
    segments = (segments + 1) / 2;

    float start = rotate * M_PI / 180.0f;
    float step = M_PI / segments;

    Internal::Vertex* v = Internal::Batch_Allocate(segments * 3);

    for (int i = 0; i < segments; i++) {
        float a0 = start + i * step;
        float a1 = start + (i + 1) * step;

        Vector2 p0(center.x + std::cos(a0) * radius, center.y + std::sin(a0) * radius);
        Vector2 p1(center.x + std::cos(a1) * radius, center.y + std::sin(a1) * radius);

        v[i * 3 + 0] = {center, color};
        v[i * 3 + 1] = {p0, color};
        v[i * 3 + 2] = {p1, color};
    }
}

void DrawLine(const Vector2 from, const Vector2 to, const Color& color, const int thickness) {
    float dx = to.x - from.x;
    float dy = to.y - from.y;
    float length = std::sqrt(dx * dx + dy * dy);
    if (length <= 0.0f || thickness <= 0) return;

    float half = static_cast<float>(thickness) / 2.0f;
    float nx = -dy / length * half;
    float ny = dx / length * half;

    Vector2 a(from.x + nx, from.y + ny);
    Vector2 b(to.x + nx, to.y + ny);
    Vector2 d(from.x - nx, from.y - ny);
    Vector2 e(to.x - nx, to.y - ny);

    Internal::Vertex* v = Internal::Batch_Allocate(6);
    v[0] = {a, color};
    v[1] = {b, color};
    v[2] = {d, color};

    v[3] = {b, color};
    v[4] = {e, color};
    v[5] = {d, color};
}

void DrawRoundedLine(const Vector2 from, const Vector2 to, const Color& color, const int thickness) {
    if (thickness <= 0) return;

    float dx = to.x - from.x;
    float dy = to.y - from.y;
    float length = std::sqrt(dx * dx + dy * dy);
    float r = thickness / 2.0f;   // float osztás, hogy páratlan vastagságnál se vesszen el a fél

    // Ha a vonal rövidebb a vastagságánál, a két kerek vég összeér: ez egy kör
    if (length <= thickness) {
        DrawCircle(Vector2((from.x + to.x) / 2, (from.y + to.y) / 2), r, color);
        return;
    }

    // Egységnyi irányvektor
    float ux = dx / length;
    float uy = dy / length;

    // A vonal végeit r-rel befelé húzzuk, hogy a félkörökkel együtt pontosan from-tól to-ig érjen
    Vector2 start(from.x + ux * r, from.y + uy * r);
    Vector2 end(to.x - ux * r, to.y - uy * r);

    DrawLine(start, end, color, thickness);

    // A DrawSemicircle fokot vár, az atan2 radiánt ad
    float angleDeg = std::atan2(dy, dx) * 180.0f / M_PI;

    // A félkör domború oldala a rotate + 90° irányba néz
    DrawSemicircle(start, r, angleDeg + 90.0f, color);   // hátra néz (a vonal iránya + 180°)
    DrawSemicircle(end,   r, angleDeg - 90.0f, color);   // előre néz (a vonal iránya)
}

void DrawPolygon(const Vector2 center, float size, const int vertices, const Color& color) {
    if (vertices < 3) return;
    if (size < 1.0f) return;

    float angle = (vertices == 4) ? 45.0f : -90.0f;

    float step = 2.0f * M_PI / vertices;
    float start = angle * M_PI / 180.0f;

    Internal::Vertex* v = Internal::Batch_Allocate(vertices * 3);

    for (int i = 0; i < vertices; i++) {
        float a0 = start + i * step;
        float a1 = start + (i + 1) * step;

        Vector2 p0(center.x + std::cos(a0) * size, center.y + std::sin(a0) * size);
        Vector2 p1(center.x + std::cos(a1) * size, center.y + std::sin(a1) * size);

        v[i * 3 + 0] = {center, color};
        v[i * 3 + 1] = {p0, color};
        v[i * 3 + 2] = {p1, color};
    }
}

}
