//
//  Font.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 15..
//

#pragma once

#include "../Texture/Texture.h"
#include <string>
#include <vector>

namespace Engine {

struct Font {
    Texture texture;
    int glyphWidth  = 8;
    int glyphHeight = 8;
    int columns     = 16;

    std::vector<uint32_t> extraGlyphs;
};

const Font& GetDefaultFont();

void DrawText(const char* text, Vector2 position, float fontSize, const Color& color);
void DrawText(const std::string& text, Vector2 position, float fontSize, const Color& color);

void DrawTextEx(const Font& font, const char* text, Vector2 position, float fontSize, float spacing, const Color& color);
void DrawTextEx(const Font& font, const std::string& text, Vector2 position, float fontSize, float spacing, const Color& color);

void DrawFPS(Vector2 position);

Vector2 MeasureText(const char* text, float fontSize);
Vector2 MeasureText(const std::string& text, float fontSize);
Vector2 MeasureTextEx(const Font& font, const char* text, float fontSize, float spacing);
Vector2 MeasureTextEx(const Font& font, const std::string& text, float fontSize, float spacing);

}
