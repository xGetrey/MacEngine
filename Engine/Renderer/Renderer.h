//
//  Renderer.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 09..
//

#pragma once
#include "../Platform/Mac/Color.h"
#include "../Core/Camera2D/Camera2D.h"

namespace Engine {

void SetClearColor(const Color& color);
void Present();

void BeginDraw();
void EndDraw();

void BeginCamera(const Camera2D& camera);
void EndCamera();

// Élsimítás (MSAA) mintaszáma: 1 = kikapcsolva, 2, 4 (alapértelmezett) vagy 8.
// Bármikor hívható; ha a GPU nem támogatja, a legközelebbi kisebb támogatott értéket használja.
void SetAntialiasing(int samples);
int GetAntialiasing();   // a ténylegesen használt mintaszám

namespace Internal {
bool Renderer_Init(void* nativeWindow);
bool Renderer_IsDrawing();
}

}
