//
//  Window.mm
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 25..
//

#import "Window.h"
#import <Cocoa/Cocoa.h>

@interface EngineWindowDelegate : NSObject <NSWindowDelegate>
@property (nonatomic, assign) bool* shouldClosePtr;
@end

@implementation EngineWindowDelegate
- (void)windowWillClose:(NSNotification *)notification {
    if (self.shouldClosePtr) {
        *self.shouldClosePtr = true;
    }
}
@end

namespace Engine {

struct Window::Impl {
    NSWindow* nsWindow = nil;
    EngineWindowDelegate* delegate = nil;
    bool shouldClose = false;
};

Window::Window(int width, int height, const std::string& title)
    : m_Impl(std::make_unique<Impl>())
{
    [NSApplication sharedApplication];
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    
    NSRect frame = NSMakeRect(100, 100, width, height);
    NSWindowStyleMask styleMask = NSWindowStyleMaskTitled |
                                  NSWindowStyleMaskClosable |
                                  NSWindowStyleMaskMiniaturizable |
                                  NSWindowStyleMaskResizable;
    
    NSWindow* window = [[NSWindow alloc] initWithContentRect:frame
                                                   styleMask:styleMask
                                                     backing:NSBackingStoreBuffered
                                                       defer:NO];
    
    NSString* nsTitle = [NSString stringWithUTF8String:title.c_str()];
    [window setTitle:nsTitle];
    
    EngineWindowDelegate* delegate = [[EngineWindowDelegate alloc] init];
    delegate.shouldClosePtr = &m_Impl->shouldClose;
    [window setDelegate:delegate];
    
    [window makeKeyAndOrderFront:nil];
    [NSApp activateIgnoringOtherApps:YES];
    
    m_Impl->nsWindow = window;
    m_Impl->delegate = delegate;
}

Window::~Window() {
    if (m_Impl) {
        if (m_Impl->nsWindow) {
            [m_Impl->nsWindow setDelegate:nil];
            [m_Impl->nsWindow close];
            m_Impl->nsWindow = nil;
        }
        m_Impl->delegate = nil;
    }
}

Window::Window(Window&&) noexcept = default;
Window& Window::operator=(Window&&) noexcept = default;

bool Window::ShouldClose() const {
    return m_Impl ? m_Impl->shouldClose : true;
}

void Window::PollEvents() {
    while (NSEvent* event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                               untilDate:[NSDate distantPast]
                                                  inMode:NSDefaultRunLoopMode
                                                 dequeue:YES]) {
        [NSApp sendEvent:event];
        [NSApp updateWindows];
    }
}

} // namespace Engine
