//
//  DisplayMetrics.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 26..
//

#pragma once

#include <string>

namespace Engine {
namespace Detail {

class DisplayMetricsImpl {
public:
    static int GetWidth();
    static int GetHeight();

    static int GetVisibleWidth();
    static int GetVisibleHeight();

    static float GetScaleFactor();
    static std::string GetDisplayID();
};

} // namespace Detail

inline Detail::DisplayMetricsImpl DisplayMetrics;

} // namespace Engine
