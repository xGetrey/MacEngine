//
//  Texture.cpp
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 14..
//

#include "Texture.h"
#include "../Batch/RenderBatch.h"
#include <cmath>
#include <utility>

namespace Engine {

void DrawTexture(const Texture& texture, Vector2 position, const Color& color) {
    float w = static_cast<float>(texture.width);
    float h = static_cast<float>(texture.height);

    DrawTexturePro(texture, Rect(0.0f, 0.0f, w, h), Rect(position, w, h), Vector2(0.0f, 0.0f), 0.0f, color);
}

void DrawTextureEx(const Texture& texture, Vector2 position, float rotation, float scale, const Color& color) {
    float w = static_cast<float>(texture.width);
    float h = static_cast<float>(texture.height);
    
    DrawTexturePro(texture, Rect(0.0f, 0.0f, w, h), Rect(position, w * scale, h * scale), Vector2(0.0f, 0.0f), rotation, color);
}

void DrawTexturePro(const Texture& texture, Rect source, Rect dest, Vector2 origin, float rotation, const Color& color) {
    if (texture.id == 0 || texture.width == 0 || texture.height == 0) return;

    bool flipX = source.width < 0.0f;
    bool flipY = source.height < 0.0f;
    float srcW = std::fabs(source.width);
    float srcH = std::fabs(source.height);

    float texW = static_cast<float>(texture.width);
    float texH = static_cast<float>(texture.height);

    float u0 = source.pos.x / texW;
    float v0 = source.pos.y / texH;
    float u1 = (source.pos.x + srcW) / texW;
    float v1 = (source.pos.y + srcH) / texH;

    if (flipX) std::swap(u0, u1);
    if (flipY) std::swap(v0, v1);

    Vector2 tl(-origin.x,              -origin.y);
    Vector2 tr(dest.width - origin.x,  -origin.y);
    Vector2 bl(-origin.x,              dest.height - origin.y);
    Vector2 br(dest.width - origin.x,  dest.height - origin.y);

    float rad = rotation * static_cast<float>(M_PI) / 180.0f;
    float c = std::cos(rad);
    float s = std::sin(rad);

    auto transform = [&](Vector2 p) {
        return Vector2(p.x * c - p.y * s + dest.pos.x,
                       p.x * s + p.y * c + dest.pos.y);
    };

    tl = transform(tl);
    tr = transform(tr);
    bl = transform(bl);
    br = transform(br);

    Internal::Vertex* v = Internal::Batch_Allocate(6, texture.id);
    v[0] = {tl, color, {u0, v0}};
    v[1] = {tr, color, {u1, v0}};
    v[2] = {bl, color, {u0, v1}};

    v[3] = {tr, color, {u1, v0}};
    v[4] = {br, color, {u1, v1}};
    v[5] = {bl, color, {u0, v1}};
}

}
