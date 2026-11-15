//
//  RenderBatch.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 13..
//

#pragma once

#include <cstddef>
#include <vector>
#include "../../Core/Vector2.h"
#include "../../Platform/Mac/Color.h"
#include <cstdint>

namespace Engine::Internal {

// Egy csúcs: 6 float egymás után, rés nélkül (a shaderben packed_float2 + packed_float4)
struct Vertex {
    Vector2 position;
    Color color;
    Vector2 uv;
};
static_assert(sizeof(Vertex) == 32, "...8 float, rés nélkül");

struct DrawCommand {
    uint32_t texture;
    size_t firstVertex;
    size_t vertexCount;
};

// count darab csúcsnak foglal helyet, és az első új csúcsra mutató pointert adja vissza.
// A pointer csak a következő Batch_Allocate hívásig érvényes (a vector átköltözhet).
Vertex* Batch_Allocate(size_t count, uint32_t texture = 0);

const std::vector<Vertex>& Batch_GetVertices();
const std::vector<DrawCommand>& Batch_GetCommands();
void Batch_Clear();

}
