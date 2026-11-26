//
//  Color.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 25..
//

#pragma once

#include <cstdint>

namespace Engine {

struct Color {
    float red = 0.0f;
    float green = 0.0f;
    float blue = 0.0f;
    float alpha = 1.0f;
    
    constexpr Color() = default;

    constexpr Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
        : red(red / 255.0f),
          green(green / 255.0f),
          blue(blue / 255.0f),
          alpha(alpha / 255.0f) {}
};

}
