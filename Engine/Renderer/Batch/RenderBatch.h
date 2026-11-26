//
//  RenderBatch.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 13..
//

#pragma once

#include <cstddef>
#include <vector>
#include "../../Core/Vector2/Vector2.h"
#include "../../Core/Color/Color.h"
#include "../../Core/Camera2D/Camera2D.h"
#include <cstdint>

namespace Engine::Internal {

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
    uint32_t camera;
};

Vertex* Batch_Allocate(size_t count, uint32_t texture = 0);

const std::vector<Vertex>& Batch_GetVertices();
const std::vector<DrawCommand>& Batch_GetCommands();
void Batch_Clear();

void Batch_SetCamera(const Camera2D& camera);
void Batch_ResetCamera();
const std::vector<Camera2D>& Batch_GetCameras();

}
