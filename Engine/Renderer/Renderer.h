//
//  Renderer.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 09..
//

#pragma once
#include "../Core/Color/Color.h"
#include "../Core/Camera2D/Camera2D.h"

namespace Engine {

void SetClearColor(const Color& color);
void Present();

void BeginDraw();
void EndDraw();

void BeginCamera(const Camera2D& camera);
void EndCamera();

void SetAntialiasing(int samples);
int GetAntialiasing();

namespace Internal {
bool Renderer_Init(void* nativeWindow);
bool Renderer_IsDrawing();
}

}
