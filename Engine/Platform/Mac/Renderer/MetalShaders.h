//
//  MetalShaders.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 13..
//

#pragma once

namespace Engine::Internal {

// A shader futásidőben fordul (newLibraryWithSource), mert a parancssori targetnek nincs app bundle-je
inline const char* kShaderSource = R"(
#include <metal_stdlib>
using namespace metal;

// packed_: rés nélkül, pontosan úgy, mint a C++ oldali Internal::Vertex (6 float)
struct Vertex {
    packed_float2 position;
    packed_float4 color;
};

struct VSOut {
    float4 position [[position]];
    float4 color;
};

vertex VSOut vs_main(uint vid [[vertex_id]],
                     const device Vertex* vertices [[buffer(0)]],
                     constant float2& viewport   [[buffer(1)]]) {
    Vertex v = vertices[vid];

    // pixel (bal felső 0,0) → Metal (-1..1, Y felfelé)
    float2 ndc = float2(v.position.x / viewport.x * 2.0 - 1.0,
                        1.0 - v.position.y / viewport.y * 2.0);

    VSOut out;
    out.position = float4(ndc, 0.0, 1.0);
    out.color = v.color;
    return out;
}

fragment float4 fs_main(VSOut in [[stage_in]]) {
    return in.color;
}
)";

}
