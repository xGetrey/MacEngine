//
//  MetalShaders.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 13..
//

#pragma once

namespace Engine::Internal {

inline const char* kShaderSource = R"(
#include <metal_stdlib>
using namespace metal;

struct Vertex {
    packed_float2 position;
    packed_float4 color;
    packed_float2 uv;
};

struct VSOut {
    float4 position [[position]];
    float4 color;
    float2 uv;
};

struct CameraData {
    float2 target;
    float2 offset;
    float2 rotation;
    float  zoom;
};

vertex VSOut vs_main(uint vid [[vertex_id]],
                     const device Vertex* vertices [[buffer(0)]],
                     constant float2& viewport     [[buffer(1)]],
                     constant CameraData& camera   [[buffer(2)]]) {
    Vertex v = vertices[vid];

    float2 p = (float2(v.position) - camera.target) * camera.zoom;
    p = float2(p.x * camera.rotation.x - p.y * camera.rotation.y,
               p.x * camera.rotation.y + p.y * camera.rotation.x);
    p += camera.offset;

    float2 ndc = float2(p.x / viewport.x * 2.0 - 1.0,
                        1.0 - p.y / viewport.y * 2.0);

    VSOut out;
    out.position = float4(ndc, 0.0, 1.0);
    out.color = v.color;
    out.uv = v.uv;
    return out;
}

fragment float4 fs_main(VSOut in [[stage_in]],
                        texture2d<float> tex [[texture(0)]]) {
    constexpr sampler s(filter::nearest, address::clamp_to_edge);

    float4 tint = float4(in.color.rgb * in.color.a, in.color.a);
    return tex.sample(s, in.uv) * tint;
}
)";

}
