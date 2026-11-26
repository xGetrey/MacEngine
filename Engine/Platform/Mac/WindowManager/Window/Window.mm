//
//  Window.mm
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 25..
//

#import "Window.h"
#import <Cocoa/Cocoa.h>
#include <Carbon/Carbon.h>

#include <iostream>
#include "../../Input/Input.h"
#include "../../Input/MacKeyMap.h"
#include "../../../../Core/Time/Time.h"
#include "../../Display/DisplayMetrics.h"
#include "../../../../Renderer/Renderer.h"

@interface EngineWindowDelegate : NSObject <NSWindowDelegate>
@property (nonatomic, assign) bool* shouldClosePtr;
@end

@implementation EngineWindowDelegate
- (void)windowWillClose:(NSNotification *)notification {
    if (self.shouldClosePtr) {
        *self.shouldClosePtr = true;
    }
}
- (void)windowDidResignKey:(NSNotification *)notification {
    Engine::Internal::Input_ClearAll();
    Engine::ClearPressedKeys();
}
@end

namespace Engine {

struct Window::Impl {
    NSWindow* nsWindow = nil;
    EngineWindowDelegate* delegate = nil;
    bool shouldClose = false;
    id layoutObserver = nil;
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
    [window setAcceptsMouseMovedEvents:YES];
    
    EngineWindowDelegate* delegate = [[EngineWindowDelegate alloc] init];
    delegate.shouldClosePtr = &m_Impl->shouldClose;
    [window setDelegate:delegate];
    
    [window makeKeyAndOrderFront:nil];
    [NSApp activateIgnoringOtherApps:YES];
    
    m_Impl->nsWindow = window;
    Internal::Renderer_Init((__bridge void*)window);
    m_Impl->delegate = delegate;
    
    Internal::Time_Init();

    RebuildLayoutTable();
    m_Impl->layoutObserver = [[NSDistributedNotificationCenter defaultCenter]
        addObserverForName:(__bridge NSString*)kTISNotifySelectedKeyboardInputSourceChanged
                    object:nil
                     queue:[NSOperationQueue mainQueue]
                usingBlock:^(NSNotification*) { RebuildLayoutTable(); }];

    SetTargetFps(Engine::DisplayMetrics.GetDisplayHz());
    
#ifdef MACENGINE_DEFAULT_ICON
    Window::Get().SetIcon(MACENGINE_DEFAULT_ICON);
#else
    Window::Get().SetIcon("Engine/MacEngineIcon.png");
#endif
}

Window::~Window() {
    s_Instance = nullptr;
    if (m_Impl) {
        if (m_Impl->nsWindow) {
            [m_Impl->nsWindow setDelegate:nil];
            [m_Impl->nsWindow close];
            m_Impl->nsWindow = nil;
        }
        if (m_Impl->layoutObserver) {
            [[NSDistributedNotificationCenter defaultCenter] removeObserver:m_Impl->layoutObserver];
            m_Impl->layoutObserver = nil;
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
    Internal::Time_BeginFrame();
    Internal::Input_BeginFrame();
    while (NSEvent* event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                               untilDate:[NSDate distantPast]
                                                  inMode:NSDefaultRunLoopMode
                                                 dequeue:YES]) {
        NSEventType type = event.type;
        if (type == NSEventTypeKeyDown || type == NSEventTypeKeyUp) {
            bool down = (type == NSEventTypeKeyDown);
            Key key = down ? LogicalKeyDown(event.keyCode) : LogicalKeyUp(event.keyCode);
            Internal::Input_SetKey(key, down);
            Internal::Input_SetPhysicalKey(TranslateKey(event.keyCode), down);
            bool cmd = (event.modifierFlags & NSEventModifierFlagCommand) != 0;
            if (!cmd) continue;

        }
        
        if (type == NSEventTypeFlagsChanged) {
            // A módosítók nem függnek a kiosztástól: logikailag és fizikailag is ugyanazok
            Key modifier = TranslateKey(event.keyCode);
            bool down = IsModifierDown(event.keyCode, event.modifierFlags);
            Internal::Input_SetKey(modifier, down);
            Internal::Input_SetPhysicalKey(modifier, down);
        }
        
        switch (type) {
            case NSEventTypeLeftMouseDown:  Internal::Input_SetMouseButton(MouseButton::Left, true);   break;
            case NSEventTypeLeftMouseUp:    Internal::Input_SetMouseButton(MouseButton::Left, false);  break;
            case NSEventTypeRightMouseDown: Internal::Input_SetMouseButton(MouseButton::Right, true);  break;
            case NSEventTypeRightMouseUp:   Internal::Input_SetMouseButton(MouseButton::Right, false); break;
            case NSEventTypeOtherMouseDown:
                if (event.buttonNumber == 2) Internal::Input_SetMouseButton(MouseButton::Middle, true);
                break;
            case NSEventTypeOtherMouseUp:
                if (event.buttonNumber == 2) Internal::Input_SetMouseButton(MouseButton::Middle, false);
                break;
            case NSEventTypeScrollWheel:
                Internal::Input_AddScroll(event.scrollingDeltaX, event.scrollingDeltaY);
                break;
            default: break;
        }

        switch (type) {
            case NSEventTypeMouseMoved:
            case NSEventTypeLeftMouseDragged:
            case NSEventTypeRightMouseDragged:
            case NSEventTypeOtherMouseDragged:
                Internal::Input_AddMouseDelta(event.deltaX, event.deltaY);
                [[fallthrough]];
            case NSEventTypeLeftMouseDown:
            case NSEventTypeRightMouseDown:
            case NSEventTypeOtherMouseDown:
                if (event.window == m_Impl->nsWindow) {
                    NSPoint p = [event locationInWindow];
                    Internal::Input_SetMousePosition(p.x, GetWindowHeight() - p.y);
                }
                break;
            default: break;
        }

        [NSApp sendEvent:event];
        [NSApp updateWindows];
    }
}

void Window::SetBackgroundColor(const Color& color) {
    if (m_Impl && m_Impl->nsWindow) {
        NSColor* nsColor = [NSColor colorWithRed:color.red green:color.green blue:color.blue alpha:color.alpha];
        [m_Impl->nsWindow setBackgroundColor:nsColor];
    }
    SetClearColor(color);
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

bool Window::SetIcon(const std::string filepath) {
    NSString *nsPath = [NSString stringWithUTF8String:filepath.c_str()];
    NSImage *icon = [[NSImage alloc] initWithContentsOfFile:nsPath];
    
    if (!icon) {
        std::cout << "Set icon fail!" << std::endl;
        return false;
    }
    
    [NSApp setApplicationIconImage:icon];
    return true;
}

} // namespace Engine
