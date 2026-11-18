//
//  RenderBatch.cpp
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 13..
//

#include "RenderBatch.h"
#include "../Renderer.h"
#include <iostream>

namespace {
std::vector<Engine::Internal::Vertex> s_Vertices;
std::vector<Engine::Internal::DrawCommand> s_Commands;

std::vector<Engine::Camera2D> s_Cameras = { Engine::Camera2D() };
uint32_t s_CurrentCamera = 0;
}

namespace Engine::Internal {

Vertex* Batch_Allocate(size_t count, uint32_t texture) {
    if (!Renderer_IsDrawing()) {
        static bool warned = false;
        if (!warned) {
            std::cerr << "[Renderer] Rajzolás a BeginDraw() előtt vagy az EndDraw() után!" << std::endl;
            warned = true;
        }
    }
    size_t oldSize = s_Vertices.size();
    s_Vertices.resize(oldSize + count);

    // Ha az előző parancs is ezt a textúrát használja, csak megnöveljük (egy rajzolási hívás marad).
    // Ha más textúra jön, új parancsot kezdünk, ami pont ott indul, ahol az előző véget ért.
    if (!s_Commands.empty() &&
        s_Commands.back().texture == texture &&
        s_Commands.back().camera == s_CurrentCamera) {
        s_Commands.back().vertexCount += count;
    } else {
        s_Commands.push_back({ texture, oldSize, count, s_CurrentCamera });
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
    s_Cameras.resize(1);    // csak a 0. (semleges) kamera marad
    s_CurrentCamera = 0;
}

void Batch_SetCamera(const Camera2D& camera) {
    s_Cameras.push_back(camera);
    s_CurrentCamera = static_cast<uint32_t>(s_Cameras.size() - 1);
}

void Batch_ResetCamera() {
    s_CurrentCamera = 0;
}

const std::vector<Camera2D>& Batch_GetCameras() {
    return s_Cameras;
}

}
