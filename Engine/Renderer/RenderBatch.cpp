//
//  RenderBatch.cpp
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 13..
//

#include "RenderBatch.h"

namespace {
std::vector<Engine::Internal::Vertex> s_Vertices;
}

namespace Engine::Internal {

Vertex* Batch_Allocate(size_t count) {
    size_t oldSize = s_Vertices.size();
    s_Vertices.resize(oldSize + count);
    return s_Vertices.data() + oldSize;
}

const std::vector<Vertex>& Batch_GetVertices() {
    return s_Vertices;
}

// A clear() megtartja a kapacitást, így a következő képkockában nem kell újrafoglalni
void Batch_Clear() {
    s_Vertices.clear();
}

}
