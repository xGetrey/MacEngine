//
//  Renderer.cpp
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 18..
//

#include "Renderer.h"
#include <iostream>
#include "Batch/RenderBatch.h"

namespace {
bool s_Drawing = false;   // BeginDraw és EndDraw között true
bool s_CameraActive = false;   // BeginCamera és EndCamera között true
}

namespace Engine {

void BeginDraw() {
    if (s_Drawing) {
        std::cerr << "[Renderer] BeginDraw() kétszer hívva, EndDraw() nélkül!" << std::endl;
    }
    s_Drawing = true;
}

void EndDraw() {
    if (!s_Drawing) {
        std::cerr << "[Renderer] EndDraw() hívva BeginDraw() nélkül!" << std::endl;
    }
    if (s_CameraActive) {
        std::cerr << "[Renderer] EndCamera() hiányzik, automatikusan lezárva." << std::endl;
        EndCamera();
    }
    s_Drawing = false;
    Present();
}

void BeginCamera(const Camera2D& camera) {
    if (!s_Drawing) {
        std::cerr << "[Renderer] BeginCamera() a BeginDraw() előtt!" << std::endl;
    }
    if (s_CameraActive) {
        std::cerr << "[Renderer] BeginCamera() kétszer, EndCamera() nélkül!" << std::endl;
    }
    Internal::Batch_SetCamera(camera);
    s_CameraActive = true;
}

void EndCamera() {
    if (!s_CameraActive) {
        std::cerr << "[Renderer] EndCamera() BeginCamera() nélkül!" << std::endl;
    }
    Internal::Batch_ResetCamera();
    s_CameraActive = false;
}

namespace Internal {
bool Renderer_IsDrawing() {
    return s_Drawing;
}
}

}
