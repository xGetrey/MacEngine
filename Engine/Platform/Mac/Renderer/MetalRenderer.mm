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
#include "../../../Renderer/RenderBatch.h"
#include "MetalShaders.h"

namespace {
id<MTLDevice> s_Device = nil;
id<MTLCommandQueue> s_Queue = nil;
CAMetalLayer* s_Layer = nil;
NSView* ns_View = nil;
MTLClearColor s_ClearColor = MTLClearColorMake(0, 0, 0, 1);
id<MTLRenderPipelineState> s_Pipeline = nil;
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

        const auto& vertices = Internal::Batch_GetVertices();

        id<CAMetalDrawable> drawable = [s_Layer nextDrawable];
        if (!drawable) {
            // Nincs mire rajzolni (pl. kicsinyített ablak): a csúcsokat akkor is el kell dobni,
            // különben a következő képkockában halmozódnának
            Internal::Batch_Clear();
            return;
        }

        MTLRenderPassDescriptor* pass = [MTLRenderPassDescriptor renderPassDescriptor];
        pass.colorAttachments[0].texture = drawable.texture;
        pass.colorAttachments[0].loadAction = MTLLoadActionClear;
        pass.colorAttachments[0].clearColor = s_ClearColor;
        pass.colorAttachments[0].storeAction = MTLStoreActionStore;

        id<MTLCommandBuffer> cmd = [s_Queue commandBuffer];
        id<MTLRenderCommandEncoder> enc = [cmd renderCommandEncoderWithDescriptor:pass];

        if (!vertices.empty()) {
            [enc setRenderPipelineState:s_Pipeline];

            id<MTLBuffer> vb = [s_Device newBufferWithBytes:vertices.data()
                                                     length:vertices.size() * sizeof(Internal::Vertex)
                                                    options:MTLResourceStorageModeShared];
            [enc setVertexBuffer:vb offset:0 atIndex:0];        // → [[buffer(0)]]

            simd_float2 viewport = { (float)size.width, (float)size.height };
            [enc setVertexBytes:&viewport length:sizeof(viewport) atIndex:1];   // → [[buffer(1)]]

            [enc drawPrimitives:MTLPrimitiveTypeTriangle
                    vertexStart:0
                    vertexCount:vertices.size()];
        }

        Internal::Batch_Clear();

        [enc endEncoding];

        [cmd presentDrawable:drawable];
        [cmd commit];
    }
}

}
