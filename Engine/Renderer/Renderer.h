//
//  Render.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 09..
//

#pragma once
#include "../Platform/Mac/Color.h"
#include "../Core/Rect/Rect.h"

namespace Engine {

void SetClearColor(const Color& color);
void Present();

void DrawRect(const Rect& rect, const Color& color);
void DrawRectLines(const Rect& rect, const Color& color, int thickness = 1);

void DrawCircle(const Vector2 center, const float radius, const Color& color);
void DrawSemicircle(const Vector2 center, const float radius, const float rotate, const Color& color);

void DrawLine(const Vector2 from, const Vector2 to, const Color& color, const int thickness = 1);
void DrawRoundedLine(const Vector2 from, const Vector2 to, const Color& color, const int thickness = 1);

void DrawPolygon(const Vector2 center, float size, const int vertices, const Color& color);

namespace Internal {
bool Renderer_Init(void* nativeWindow);
}

}
