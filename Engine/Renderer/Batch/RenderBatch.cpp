//
//  RenderBatch.cpp
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 13..
//

#include "RenderBatch.h"

namespace {
std::vector<Engine::Internal::Vertex> s_Vertices;
std::vector<Engine::Internal::DrawCommand> s_Commands;
}

namespace Engine::Internal {

Vertex* Batch_Allocate(size_t count, uint32_t texture) {
    size_t oldSize = s_Vertices.size();
    s_Vertices.resize(oldSize + count);

    // Ha az előző parancs is ezt a textúrát használja, csak megnöveljük (egy rajzolási hívás marad).
    // Ha más textúra jön, új parancsot kezdünk, ami pont ott indul, ahol az előző véget ért.
    if (!s_Commands.empty() && s_Commands.back().texture == texture) {
        s_Commands.back().vertexCount += count;
    } else {
        s_Commands.push_back({ texture, oldSize, count });
    }

    return s_Vertices.data() + oldSize;
}

const std::vector<Vertex>& Batch_GetVertices() {
    return s_Vertices;
}

const std::vector<DrawCommand>& Batch_GetCommands() {
    return s_Commands;
}

// A clear() megtartja a kapacitást, így a következő képkockában nem kell újrafoglalni
void Batch_Clear() {
    s_Vertices.clear();
    s_Commands.clear();
}

}
