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

namespace {
id<MTLDevice> s_Device = nil;
id<MTLCommandQueue> s_Queue = nil;
CAMetalLayer* s_Layer = nil;
NSView* ns_View = nil;
MTLClearColor s_ClearColor = MTLClearColorMake(0, 0, 0, 1);
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
    return true;
}
}

void SetClearColor(const Color& color) {
    s_ClearColor = MTLClearColorMake(color.red, color.green, color.blue, color.alpha);
}

void Present() {
    @autoreleasepool {
        // A vászon mérete kövesse az ablakot (átméretezés, Retina)
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
        // ← ide jönnek majd a rajzolási parancsok (négyzet)
        [enc endEncoding];

        [cmd presentDrawable:drawable];
        [cmd commit];
    }
}

}

