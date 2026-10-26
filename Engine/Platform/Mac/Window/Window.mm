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

Window::Window(int width, int height, const std::string& title) : m_Impl(std::make_unique<Impl>()) {
    s_Instance = this;
    [NSApplication sharedApplication]; //elindítja az alkalmazást
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    
    NSRect frame = NSMakeRect(100, 100, width, height);
    NSWindowStyleMask styleMask = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable;
    
    NSWindow* window = [[NSWindow alloc] initWithContentRect:frame
                                                   styleMask:styleMask
                                                     backing:NSBackingStoreBuffered
                                                       defer:NO];
    
    NSString* nsTitle = [NSString stringWithUTF8String:title.c_str()];
    [window setTitle:nsTitle];
    [window center];
    
    EngineWindowDelegate* delegate = [[EngineWindowDelegate alloc] init];
    delegate.shouldClosePtr = &m_Impl->shouldClose;
    [window setDelegate:delegate];
    
    [window makeKeyAndOrderFront:nil];
    [NSApp activateIgnoringOtherApps:YES];
    
    m_Impl->nsWindow = window;
    m_Impl->delegate = delegate;
}

Window::~Window() {
    s_Instance = nullptr;
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

void Window::SetBackgroundColor(const Color& color) {
    if (m_Impl && m_Impl->nsWindow) {
        NSColor* nsColor = [NSColor colorWithRed:color.red green:color.green blue:color.blue alpha:color.alpha];
        [m_Impl->nsWindow setBackgroundColor:nsColor];
    }
}

bool Window::IsResizable() const {
    if (!m_Impl || !m_Impl->nsWindow) return false;
    return (m_Impl->nsWindow.styleMask & NSWindowStyleMaskResizable) != 0;
}

bool Window::IsClosable() const {
    if (!m_Impl || !m_Impl->nsWindow) return false;
    return (m_Impl->nsWindow.styleMask & NSWindowStyleMaskClosable) != 0;
}

bool Window::IsMiniaturizable() const {
    if (!m_Impl || !m_Impl->nsWindow) return false;
    return (m_Impl->nsWindow.styleMask & NSWindowStyleMaskMiniaturizable) != 0;
}

void Window::SetResizable(bool resizable) {
    if (IsResizable() != resizable) {
        if (resizable) {
            m_Impl->nsWindow.styleMask |= NSWindowStyleMaskResizable;
        } else {
            m_Impl->nsWindow.styleMask &= ~NSWindowStyleMaskResizable;
        }
    }
}

void Window::SetClosable(bool closable) {
    if (IsClosable() != closable) {
        if (closable) {
            m_Impl->nsWindow.styleMask |= NSWindowStyleMaskClosable;
        } else {
            m_Impl->nsWindow.styleMask &= ~NSWindowStyleMaskClosable;
        }
    }
}

void Window::SetMiniaturizable(bool miniaturizable) {
    if (IsMiniaturizable() != miniaturizable) {
        if (miniaturizable) {
            m_Impl->nsWindow.styleMask |= NSWindowStyleMaskMiniaturizable;
        } else {
            m_Impl->nsWindow.styleMask &= ~NSWindowStyleMaskMiniaturizable;
        }
    }
}

int Window::GetWindowWidth() const {
    if (!m_Impl || !m_Impl->nsWindow) return 0;
    NSRect bounds = [[m_Impl->nsWindow contentView] bounds];
    return static_cast<int>(bounds.size.width);
}

int Window::GetWindowHeight() const {
    if (!m_Impl || !m_Impl->nsWindow) return 0;
    NSRect bounds = [[m_Impl->nsWindow contentView] bounds];
    return static_cast<int>(bounds.size.height);
}

} // namespace Engine
