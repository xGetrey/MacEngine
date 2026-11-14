//
//  Texture.cpp
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 14..
//

#include "Texture.h"
#include "RenderBatch.h"

namespace Engine {

void DrawTexture(const Texture& texture, Vector2 position, const Color& color) {
    if (texture.id == 0) return;
    
    float w = static_cast<float>(texture.width);
    float h = static_cast<float>(texture.height);
    
    Vector2 tl(position.x, position.y);
    Vector2 tr(position.x + w, position.y);
    Vector2 bl(position.x, position.y + h);
    Vector2 br(position.x + w, position.y + h);
    
    Internal::Vertex* v = Internal::Batch_Allocate(6, texture.id);
    v[0] = {tl, color, {0.0f, 0.0f}};
    v[1] = {tr, color, {1.0f, 0.0f}};
    v[2] = {bl, color, {0.0f, 1.0f}};
    
    v[3] = {tr, color, {1.0f, 0.0f}};
    v[4] = {br, color, {1.0f, 1.0f}};
    v[5] = {bl, color, {0.0f, 1.0f}};
}

}
