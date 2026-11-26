//
//  MacEngine.hpp
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 25..
//

#pragma once

#include "Platform/Mac/WindowManager/Window/Window.h"
#include "Core/Color/Color.h"
#include "Platform/Mac/Display/DisplayMetrics.h"
#include "Platform/Mac/WindowManager/Menubar/MenubarAPI.h"
#include "Core/Input/Input.h"
#include "Core/Vector2/Vector2.h"
#include "Core/Time/Time.h"
#include "Core/Camera2D/Camera2D.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shapes/Shapes.h"
#include "Renderer/Texture/Texture.h"
#include "Renderer/Text/Font.h"

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

}
