//
//  RenderBatch.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 13..
//

#pragma once

#include <cstddef>
#include <vector>
#include "../Core/Vector2.h"
#include "../Platform/Mac/Color.h"

namespace Engine::Internal {

// Egy csúcs: 6 float egymás után, rés nélkül (a shaderben packed_float2 + packed_float4)
struct Vertex {
    Vector2 position;
    Color color;
};
static_assert(sizeof(Vertex) == 24, "A Vertex mérete egyezzen a shaderével (6 float, rés nélkül)");

// count darab csúcsnak foglal helyet, és az első új csúcsra mutató pointert adja vissza.
// A pointer csak a következő Batch_Allocate hívásig érvényes (a vector átköltözhet).
Vertex* Batch_Allocate(size_t count);

const std::vector<Vertex>& Batch_GetVertices();
void Batch_Clear();

}
