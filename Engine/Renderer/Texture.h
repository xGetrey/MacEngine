//
//  Texture.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 14..
//

#pragma once

#include <cstdint>
#include "../Platform/Mac/Color.h"
#include "../Core/Vector2.h"
#include "../Core/Rect/Rect.h"

namespace Engine {

struct Texture {
    uint32_t id = 0;
    int width = 0;
    int height = 0;
};

Texture LoadTexture(const char* path);
void UnloadTexture(Texture& texture);

void DrawTexture(const Texture& texture, Vector2 position, const Color& color);
void DrawTextureEx(const Texture& texture, Vector2 position, float rotation, float scale, const Color& color);
void DrawTexturePro(const Texture& texture, Rect source, Rect dest, Vector2 origin, float rotation, const Color& color);

}
