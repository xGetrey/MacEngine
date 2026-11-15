//
//  MetalRenderer.mm
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 09..
//

#import <Cocoa/Cocoa.h>
#import <Metal/Metal.h>
#import <QuartzCore/QuartzCore.h>
#import <ImageIO/ImageIO.h>
#import "../../../Renderer/Renderer.h"

#include <simd/simd.h>
#include "../../../Renderer/RenderBatch.h"
#include "MetalShaders.h"
#include <vector>
#include "../../../Renderer/Texture.h"
#include <iostream>

namespace {
id<MTLDevice> s_Device = nil;
id<MTLCommandQueue> s_Queue = nil;
CAMetalLayer* s_Layer = nil;
NSView* ns_View = nil;
MTLClearColor s_ClearColor = MTLClearColorMake(0, 0, 0, 1);
id<MTLRenderPipelineState> s_Pipeline = nil;
id<MTLLibrary> s_Library = nil;   // a lefordított shader, a pipeline újraépítéséhez megtartjuk

// Élsimítás (MSAA): ide rajzolunk pixelenként több mintával, a végén ez olvad össze a drawable-be
id<MTLTexture> s_MSAATexture = nil;
NSUInteger s_SampleCount = 1;            // amivel a pipeline jelenleg készült
NSUInteger s_RequestedSampleCount = 4;   // amit a fejlesztő kért (SetAntialiasing)

id<MTLTexture> s_WhiteTexture = nil;
std::vector<id<MTLTexture>> s_Textures;

// A kért mintaszámhoz a legnagyobb, a GPU által támogatott értéket adja (8, 4, 2 vagy 1)
NSUInteger ResolveSampleCount(NSUInteger requested) {
    const NSUInteger options[] = { 8, 4, 2 };
    for (NSUInteger count : options) {
        if (count <= requested && [s_Device supportsTextureSampleCount:count]) return count;
    }
    return 1;
}

// A pipeline a mintaszámot is tartalmazza, ezért élsimítás váltásakor újra kell építeni
bool BuildPipeline(NSUInteger sampleCount) {
    MTLRenderPipelineDescriptor* desc = [[MTLRenderPipelineDescriptor alloc] init];
    desc.vertexFunction = [s_Library newFunctionWithName:@"vs_main"];
    desc.fragmentFunction = [s_Library newFunctionWithName:@"fs_main"];
    desc.colorAttachments[0].pixelFormat = s_Layer.pixelFormat;
    desc.rasterSampleCount = sampleCount;   // egyezzen az MSAA textúráéval

    desc.colorAttachments[0].blendingEnabled = YES;
    desc.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorOne; /// Premultiplied alfa: a shader már szorozva adja az RGB-t
    desc.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    desc.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorOne;
    desc.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorOneMinusSourceAlpha;

    NSError* error = nil;
    id<MTLRenderPipelineState> pipeline = [s_Device newRenderPipelineStateWithDescriptor:desc error:&error];
    if (!pipeline) {
        NSLog(@"Pipeline hiba: %@", error);
        return false;   // a régi pipeline marad érvényben
    }

    s_Pipeline = pipeline;
    s_SampleCount = sampleCount;
    s_MSAATexture = nil;   // az EnsureMSAATexture az új mintaszámmal hozza létre újra
    return true;
}

// Az MSAA textúra mérete mindig egyezzen a drawable méretével (átméretezés, kijelzőváltás)
void EnsureMSAATexture(NSUInteger width, NSUInteger height) {
    if (s_SampleCount <= 1) return;
    if (s_MSAATexture && s_MSAATexture.width == width && s_MSAATexture.height == height) return;

    MTLTextureDescriptor* d = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:s_Layer.pixelFormat
                                                                                 width:width
                                                                                height:height
                                                                             mipmapped:NO];
    d.textureType = MTLTextureType2DMultisample;
    d.sampleCount = s_SampleCount;
    d.usage = MTLTextureUsageRenderTarget;

    // Apple Silicon-on a memoryless textúra a GPU belső tile memóriájában él, nem foglal RAM-ot,
    // így az MSAA szinte ingyen van. Intel Mac-en ez nem támogatott, ott privát memória kell.
    d.storageMode = [s_Device supportsFamily:MTLGPUFamilyApple7] ? MTLStorageModeMemoryless
                                                                 : MTLStorageModePrivate;

    s_MSAATexture = [s_Device newTextureWithDescriptor:d];
}
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
    // Átméretezés közben (amíg még a régi méretű kép látszik) se mosódjon el
    s_Layer.magnificationFilter = kCAFilterNearest;

    ns_View = window.contentView;
    ns_View.wantsLayer = YES;
    ns_View.layer = s_Layer;

    s_Queue = [s_Device newCommandQueue];

    NSError* error = nil;
    s_Library = [s_Device newLibraryWithSource:@(kShaderSource) options:nil error:&error];
    if (!s_Library) {
        NSLog(@"Shader hiba: %@", error);
        return false;
    }
    
    MTLTextureDescriptor* whiteDesc = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:MTLPixelFormatRGBA8Unorm width:1 height:1 mipmapped:NO];
    whiteDesc.usage = MTLTextureUsageShaderRead;
    s_WhiteTexture = [s_Device newTextureWithDescriptor:whiteDesc];
    
    const uint8_t white[4] = { 255, 255, 255, 255 };
    [s_WhiteTexture replaceRegion:MTLRegionMake2D(0, 0, 1, 1) mipmapLevel:0 withBytes:white bytesPerRow:4];
    
    s_Textures.push_back(s_WhiteTexture);

    return BuildPipeline(ResolveSampleCount(s_RequestedSampleCount));
}
}

void SetClearColor(const Color& color) {
    s_ClearColor = MTLClearColorMake(color.red, color.green, color.blue, color.alpha);
}

void SetAntialiasing(int samples) {
    // Csak feljegyezzük; a pipeline-t a következő Present() építi újra.
    // Így a Window létrehozása előtt és futás közben is hívható.
    s_RequestedSampleCount = samples < 1 ? 1 : static_cast<NSUInteger>(samples);
}

int GetAntialiasing() {
    return static_cast<int>(s_SampleCount);
}

void Present() {
    @autoreleasepool {
        // Ha a fejlesztő más élsimítást kért, mint amivel a pipeline készült, újraépítjük
        NSUInteger wanted = ResolveSampleCount(s_RequestedSampleCount);
        if (wanted != s_SampleCount) BuildPipeline(wanted);

        // Mindig az aktuális kijelző skálája (Retina ↔ sima monitor között áthúzva se mosódjon el)
        CGFloat scale = ns_View.window.backingScaleFactor;
        CGSize size = ns_View.bounds.size;
        CGSize drawableSize = CGSizeMake(size.width * scale, size.height * scale);

        // Csak változáskor állítjuk, mert a drawableSize beállítása új textúrák foglalását okozhatja
        if (s_Layer.contentsScale != scale) s_Layer.contentsScale = scale;
        if (!CGSizeEqualToSize(s_Layer.drawableSize, drawableSize)) s_Layer.drawableSize = drawableSize;

        const auto& vertices = Internal::Batch_GetVertices();

        id<CAMetalDrawable> drawable = [s_Layer nextDrawable];
        if (!drawable) {
            // Nincs mire rajzolni (pl. kicsinyített ablak): a csúcsokat akkor is el kell dobni,
            // különben a következő képkockában halmozódnának
            Internal::Batch_Clear();
            return;
        }

        EnsureMSAATexture(drawable.texture.width, drawable.texture.height);

        MTLRenderPassDescriptor* pass = [MTLRenderPassDescriptor renderPassDescriptor];
        if (s_SampleCount > 1) {
            pass.colorAttachments[0].texture = s_MSAATexture;           // ide rajzol (több minta/pixel)
            pass.colorAttachments[0].resolveTexture = drawable.texture; // ide olvasztja össze
            pass.colorAttachments[0].storeAction = MTLStoreActionMultisampleResolve;
        } else {
            pass.colorAttachments[0].texture = drawable.texture;
            pass.colorAttachments[0].storeAction = MTLStoreActionStore;
        }
        pass.colorAttachments[0].loadAction = MTLLoadActionClear;
        pass.colorAttachments[0].clearColor = s_ClearColor;

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
            for (const auto& command : Internal::Batch_GetCommands()) {
                id<MTLTexture> texture = s_WhiteTexture;
                if (command.texture < s_Textures.size() && s_Textures[command.texture]) {
                    texture = s_Textures[command.texture];
                }
                
                [enc setFragmentTexture:texture atIndex:0];
                [enc drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:command.firstVertex vertexCount:command.vertexCount];
            }
        }

        Internal::Batch_Clear();

        [enc endEncoding];

        [cmd presentDrawable:drawable];
        [cmd commit];
    }
}

Texture LoadTexture(const char* path) {
    Texture result;
    
    if (!s_Device) {
        NSLog(@"LoadTexture: előbb hozd létre a Window-t! (%s)", path);
        return result;
    }
    
    NSURL* url = [NSURL fileURLWithPath:@(path)];
    CGImageSourceRef source = CGImageSourceCreateWithURL((__bridge CFURLRef)url, nullptr);
    
    if (!source) {
        NSLog(@"LoadTexture: nem található fájl: %s", path);
        return result;
    }
    
    CGImageRef image = CGImageSourceCreateImageAtIndex(source, 0, nullptr);
    CFRelease(source);
    if(!image) {
        NSLog(@"LoadTexture: nem sikerült a képet beolvasni: %s", path);
        return result;
    }
    
    size_t width = CGImageGetWidth(image);
    size_t height = CGImageGetHeight(image);
    
    std::vector<uint8_t> pixels(height * width * 4);
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateWithName(kCGColorSpaceSRGB);
    CGBitmapInfo format = (CGBitmapInfo)kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big;
    CGContextRef canvas = CGBitmapContextCreate(pixels.data(), width, height, 8, width*4, colorSpace, format);
    CGColorSpaceRelease(colorSpace);
    
    if(!canvas) {
        CGImageRelease(image);
        NSLog(@"LoadTexture: nem sikerült átalakítani: %s", path);
        return result;
    }
    
    CGContextDrawImage(canvas, CGRectMake(0, 0, width, height), image);
    CGContextRelease(canvas);
    CGImageRelease(image);

    result = LoadTextureFromPixels(pixels.data(), static_cast<int>(width), static_cast<int>(height));
    if (result.id != 0) std::cout << "Texture loaded: " << path << std::endl;
    return result;
}

Texture LoadTextureFromPixels(const uint8_t* rgba, int width, int height) {
    Texture result;

    if (!s_Device) {
        NSLog(@"LoadTextureFromPixels: előbb hozd létre a Window-t!");
        return result;
    }
    if (!rgba || width <= 0 || height <= 0) return result;

    MTLTextureDescriptor* desc = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:MTLPixelFormatRGBA8Unorm width:width height:height mipmapped:NO];
    desc.usage = MTLTextureUsageShaderRead;
    id<MTLTexture> texture = [s_Device newTextureWithDescriptor:desc];

    [texture replaceRegion:MTLRegionMake2D(0, 0, width, height) mipmapLevel:0 withBytes:rgba bytesPerRow:width*4];

    s_Textures.push_back(texture);
    result.id = static_cast<uint32_t>(s_Textures.size()-1);
    result.width = width;
    result.height = height;
    return result;
}

void UnloadTexture(Texture& texture) {
    if (texture.id == 0 || texture.id >= s_Textures.size()) return;
    
    s_Textures[texture.id] = nil;
    texture = Texture{};
}

}
