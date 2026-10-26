//
//  MacEngine.hpp
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 25..
//

#pragma once

#include "Platform/Mac/Window/Window.h"
#include "Platform/Mac/Color.h"
#include "Platform/Mac/Display/DisplayMetrics.h"

namespace Engine {
inline int GetWidth() {
    return Window::Get().GetWindowWidth();
}

inline int GetHeight() {
    return Window::Get().GetWindowHeight();
}

} // Engine namespace
