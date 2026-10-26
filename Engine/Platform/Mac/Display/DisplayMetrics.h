//
//  DisplayMetrics.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 26..
//

#pragma once

#include <string>

namespace Engine {
namespace Display {

class DisplayMetrics {
public:
    static int GetWidth();
    static int GetHeight();

    static int GetVisibleWidth();
    static int GetVisibleHeight();
    
    static float GetScaleFactor();
    
    static std::string GetDisplayID();
};

} // namespace Display

} // namespace Engine
