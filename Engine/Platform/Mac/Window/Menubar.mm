//
//  Menubar.mm
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 26..
//

#import <Cocoa/Cocoa.h>
#include "Menubar.h"
#include <iostream>
#import <objc/runtime.h>

@interface MenuTargetProxy : NSObject {
    std::function<void()> m_Callback;
}
- (id)initWithCallback:(std::function<void()>)callback;
- (void)menuItemClicked:(id)sender;
@end

@implementation MenuTargetProxy
- (id)initWithCallback:(std::function<void ()>)callback {
    self = [super init];
    if (self) {
        m_Callback = callback;
    }
    return self;
}
- (void)menuItemClicked:(id)sender {
    if (m_Callback) {
        m_Callback();
    }
}
@end

namespace Engine {

Menubar& Menubar::Get() {
    static Menubar instance;
    return instance;
}

void Menubar::AddMenu(const MenuData& menu) {
    m_Menus.push_back(menu);
}

void Menubar::Build() {
    NSMenu *mainMenu = [[NSMenu alloc] init];
    
    NSMenuItem *appMenuItem = [[NSMenuItem alloc] init];
    NSMenu *appMenu = [[NSMenu alloc] init];
    [appMenu addItemWithTitle:@"Exit" action:@selector(terminate:) keyEquivalent:@"q"];
    [appMenuItem setSubmenu:appMenu];
    [mainMenu addItem:appMenuItem];
    
    for (const auto& menuData : m_Menus) {
        NSMenuItem *menuItem = [[NSMenuItem alloc] init];
        [menuItem setTitle:[NSString stringWithUTF8String:menuData.title.c_str()]];
        
        NSMenu *nsSubMenu = [[NSMenu alloc] init];
        
        for (const auto& itemData : menuData.items) {
            if (itemData.isSeparator) {
                [nsSubMenu addItem:[NSMenuItem separatorItem]];
                continue;
            }
            
            NSString *title = [NSString stringWithUTF8String:itemData.title.c_str()];
            NSString *shortcut = itemData.shortcut.empty() ? @"" : [NSString stringWithUTF8String:itemData.shortcut.c_str()];
            
            NSMenuItem *nsItem = [[NSMenuItem alloc] initWithTitle:title action:@selector(menuItemClicked:) keyEquivalent:shortcut];
            MenuTargetProxy *proxy = [[MenuTargetProxy alloc] initWithCallback:itemData.onClick];
            [nsItem setTarget:proxy];
            
            objc_setAssociatedObject(nsItem, "CPlusPlusCallbackProxy", proxy, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
            [nsSubMenu addItem:nsItem];
        }
        [menuItem setSubmenu:nsSubMenu];
        [mainMenu addItem:menuItem];
    }
    
    [NSApp setMainMenu:mainMenu];
}

}
