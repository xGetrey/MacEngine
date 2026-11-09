//
//  Render.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 09..
//

#pragma once
#include "../Platform/Mac/Color.h"

namespace Engine {

void SetClearColor(const Color& color);
void Present();

namespace Internal {
bool Renderer_Init(void* nativeWindow);
}

}
