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

namespace Internal {
bool Renderer_Init(void* nativeWindow);
}

}
