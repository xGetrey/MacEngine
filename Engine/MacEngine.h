//
//  MacEngine.hpp
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 25..
//

#pragma once

#include "Platform/Mac/WindowManager/Window/Window.h"
#include "Platform/Mac/Color.h"
#include "Platform/Mac/Display/DisplayMetrics.h"
#include "Platform/Mac/WindowManager/Menubar/MenubarAPI.h"


namespace Engine {
using MenubarApi::BuildMenubar;
using MenubarApi::menuSection;
using MenubarApi::menuItem;

inline int GetWidth() {
    return Window::Get().GetWindowWidth();
}

inline int GetHeight() {
    return Window::Get().GetWindowHeight();
}

} // Engine namespace
