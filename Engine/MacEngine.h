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
#include "Platform/Mac/WindowManager/Menubar/Menu/Menubar.h"
#include "Platform/Mac/WindowManager/Menubar/Section/MenuData.h"
#include "Platform/Mac/WindowManager/Menubar/Item/MenuItemData.h"

namespace Engine {
inline int GetWidth() {
    return Window::Get().GetWindowWidth();
}

inline int GetHeight() {
    return Window::Get().GetWindowHeight();
}

} // Engine namespace
