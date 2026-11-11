//
//  MetalRenderer.mm
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 09..
//

#import <Cocoa/Cocoa.h>
#import <Metal/Metal.h>
#import <QuartzCore/QuartzCore.h>
#import "../../../Renderer/Renderer.h"

#include <simd/simd.h>
#include <vector>
#include "../../../Core/Rect/Rect.h"

namespace {
id<MTLDevice> s_Device = nil;
id<MTLCommandQueue> s_Queue = nil;
CAMetalLayer* s_Layer = nil;
NSView* ns_View = nil;
MTLClearColor s_ClearColor = MTLClearColorMake(0, 0, 0, 1);

struct Vertex {
    simd_float2 position;
    simd_float4 color;
};

std::vector<Vertex> s_Vertices;
id<MTLRenderPipelineState> s_Pipeline = nil;

const char* kShaderSource = R"(
#include <metal_stdlib>
using namespace metal;

struct Vertex {
    float2 position;
    float4 color;
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

namespace Engine {
namespace Internal {

bool Renderer_Init(void* nativeWindow) {
    NSWindow* window = (__bridge NSWindow*)nativeWindow;
    s_Device = MTLCreateSystemDefaultDevice();
    if(!s_Device) return false;
    
    s_Layer = [CAMetalLayer layer];
    s_Layer.device = s_Device;
    s_Layer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    s_Layer.contentsScale = window.backingScaleFactor;
    
    ns_View = window.contentView;
    ns_View.wantsLayer = YES;
    ns_View.layer = s_Layer;
    
    s_Queue = [s_Device newCommandQueue];
    
    NSError* error = nil;
    id<MTLLibrary> library = [s_Device newLibraryWithSource:@(kShaderSource) options:nil error:&error];
    if (!library) {
        NSLog(@"Shader hiba: %@", error);
        return false;
    }
    
    MTLRenderPipelineDescriptor* desc = [[MTLRenderPipelineDescriptor alloc] init];
    desc.vertexFunction = [library newFunctionWithName:@"vs_main"];
    desc.fragmentFunction = [library newFunctionWithName:@"fs_main"];
    desc.colorAttachments[0].pixelFormat = s_Layer.pixelFormat;
    
    desc.colorAttachments[0].blendingEnabled = YES;
    desc.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorSourceAlpha;
    desc.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    desc.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorOne;
    desc.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    
    s_Pipeline = [s_Device newRenderPipelineStateWithDescriptor:desc error:&error];
    if (!s_Pipeline) {
        NSLog(@"Pipeline hiba: %@", error);
        return false;
    }
    
    return true;
}
}

void SetClearColor(const Color& color) {
    s_ClearColor = MTLClearColorMake(color.red, color.green, color.blue, color.alpha);
}

void Present() {
    @autoreleasepool {
        CGSize size = ns_View.bounds.size;
        CGFloat scale = s_Layer.contentsScale;
        s_Layer.drawableSize = CGSizeMake(size.width * scale, size.height * scale);
        
        id<CAMetalDrawable> drawable = [s_Layer nextDrawable];
        if (!drawable) return;
        
        MTLRenderPassDescriptor* pass = [MTLRenderPassDescriptor renderPassDescriptor];
        pass.colorAttachments[0].texture = drawable.texture;
        pass.colorAttachments[0].loadAction = MTLLoadActionClear;
        pass.colorAttachments[0].clearColor = s_ClearColor;
        pass.colorAttachments[0].storeAction = MTLStoreActionStore;
        
        id<MTLCommandBuffer> cmd = [s_Queue commandBuffer];
        id<MTLRenderCommandEncoder> enc = [cmd renderCommandEncoderWithDescriptor:pass];
        
        if (!s_Vertices.empty()) {
            [enc setRenderPipelineState:s_Pipeline];
            
            id<MTLBuffer> vb = [s_Device newBufferWithBytes:s_Vertices.data()
                                                     length:s_Vertices.size() * sizeof(Vertex)
                                                    options:MTLResourceStorageModeShared];
            [enc setVertexBuffer:vb offset:0 atIndex:0];        // → [[buffer(0)]]
            
            simd_float2 viewport = { (float)size.width, (float)size.height };
            [enc setVertexBytes:&viewport length:sizeof(viewport) atIndex:1];   // → [[buffer(1)]]
            
            [enc drawPrimitives:MTLPrimitiveTypeTriangle
                    vertexStart:0
                    vertexCount:s_Vertices.size()];
        }
        
        s_Vertices.clear();
        
        [enc endEncoding];
        
        [cmd presentDrawable:drawable];
        [cmd commit];
    }
}

void DrawRect(const Rect& rect, const Color& color) {
    simd_float4 c = { color.red, color.green, color.blue, color.alpha };
    
    simd_float2 tl = { rect.Left(), rect.Top() };
    simd_float2 tr = { rect.Right(), rect.Top() };
    simd_float2 bl = { rect.Left(), rect.Bottom() };
    simd_float2 br = { rect.Right(), rect.Bottom() };
    
    s_Vertices.push_back({tl, c});
    s_Vertices.push_back({tr, c});
    s_Vertices.push_back({bl, c});
    
    s_Vertices.push_back({tr, c});
    s_Vertices.push_back({br, c});
    s_Vertices.push_back({bl, c});
}

void DrawRectLines(const Rect& rect, const Color& color, const int thickness) {
    if (thickness == 0) {
        return;
    }
    
    float t = static_cast<float>(thickness);
    
    if (t * 2 >= rect.width || t * 2 >= rect.height) {
        DrawRect(rect, color);
        return;
    }
    
    float x = rect.Left(), y = rect.Top();
    float w = rect.width, h = rect.height;
    
    DrawRect(Rect(x, y, w, t), color);
    DrawRect(Rect(x, y + h - t, w, t), color);
    DrawRect(Rect(x, y + t, t, h  - 2 * t), color);
    DrawRect(Rect(x + w - t, y + t, t, h - 2 * t), color);
}

void DrawCircle(Vector2 center, float radius, const Color& color) {
    if (radius == 0) return;
    
    int segments = 8;
    if (radius > 0.25f) {
        segments = (int)std::ceil(M_PI / std::acos(1.0f - 0.25f / radius));
    }
    if (segments < 8) segments = 8;
    
    simd_float4 c = {color.red, color.green, color.blue, color.alpha};
    simd_float2 mid = {center.x, center.y};
    float step = 2.0f * M_PI / segments;
    
    for (int i = 0; i < segments; i++) {
        float a0 = i * step;
        float a1 = (i + 1) * step;
        
        simd_float2 p0 = {center.x + std::cos(a0) * radius, center.y + std::sin(a0) * radius};
        simd_float2 p1 = {center.x + std::cos(a1) * radius, center.y + std::sin(a1) * radius};
        
        s_Vertices.push_back({mid, c});
        s_Vertices.push_back({p0, c});
        s_Vertices.push_back({p1, c});
    }
}

void DrawLine(const Vector2 from, const Vector2 to, const Color& color, const int thickness) {
    float dx = to.x - from.x;
    float dy = to.y - from.y;
    float length = std::sqrt(dx * dx + dy * dy);
    if (length <= 0.0f || thickness <= 0) return;
    
    float half = static_cast<float>(thickness) / 2.0f;
    float nx = -dy / length * half;
    float ny = dx / length * half;
        
    simd_float4 c = {color.red, color.green, color.blue, color.alpha};
    
    simd_float2 a = {from.x + nx, from.y + ny};
    simd_float2 b = {to.x + nx, to.y + ny};
    simd_float2 d = {from.x - nx, from.y - ny};
    simd_float2 e = {to.x - nx, to.y - ny};
    
    s_Vertices.push_back({a, c});
    s_Vertices.push_back({b, c});
    s_Vertices.push_back({d, c});
    
    s_Vertices.push_back({b, c});
    s_Vertices.push_back({e, c});
    s_Vertices.push_back({d, c});
}

}
