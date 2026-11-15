//
//  Font.cpp
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 15..
//

#include "Font.h"
#include "DefaultFontData.h"
#include "../Core/Time/Time.h"
#include "../Platform/Mac/Display/DisplayMetrics.h"
#include <vector>
#include <algorithm>
#include <cmath>

namespace Engine {

namespace {

// A pozíciót a képernyő valódi pixeleihez igazítja. Retinán (scale = 2) egy pont 2 pixel,
// ezért ott fél pontokra kerekítünk. Enélkül a nearest szűrő miatt tört koordinátán
// egyes betűoszlopok vastagabbak lennének, és mozgás közben "hullámzana" a szöveg.
Vector2 SnapToPixel(Vector2 position) {
    float scale = DisplayMetrics.GetScaleFactor();
    if (scale <= 0.0f) scale = 1.0f;
    return Vector2(std::round(position.x * scale) / scale,
                   std::round(position.y * scale) / scale);
}

// Kiolvas egy karaktert (Unicode codepointot) a UTF-8 szövegből, és a p-t a következő karakterre lépteti.
// UTF-8-ban az ASCII 1 bájt, az ékezetes betűk 2 bájt (pl. 'á' = 0xC3 0xA1).
// Az első bájt eleje megmondja, hány bájtos a karakter:
//   0xxxxxxx → 1 bájt,  110xxxxx → 2,  1110xxxx → 3,  11110xxx → 4
// a többi bájt mind 10xxxxxx alakú, és mindegyik 6 bitet ad hozzá.
uint32_t NextCodepoint(const char*& p) {
    unsigned char first = static_cast<unsigned char>(*p);

    if (first < 0x80) { p++; return first; }

    int length;
    uint32_t codepoint;
    if      ((first & 0xE0) == 0xC0) { length = 2; codepoint = first & 0x1F; }
    else if ((first & 0xF0) == 0xE0) { length = 3; codepoint = first & 0x0F; }
    else if ((first & 0xF8) == 0xF0) { length = 4; codepoint = first & 0x07; }
    else { p++; return '?'; }   // hibás bájt

    for (int i = 1; i < length; i++) {
        unsigned char next = static_cast<unsigned char>(p[i]);
        // Ha nem 10xxxxxx (vagy vége a szövegnek), a karakter csonka
        if ((next & 0xC0) != 0x80) { p += i; return '?'; }
        codepoint = (codepoint << 6) | (next & 0x3F);
    }

    p += length;
    return codepoint;
}

// Melyik kockában van a betű a textúrán
int GlyphIndex(const Font& font, uint32_t codepoint) {
    if (codepoint < 128) return static_cast<int>(codepoint);

    for (size_t i = 0; i < font.extraGlyphs.size(); i++) {
        if (font.extraGlyphs[i] == codepoint) return 128 + static_cast<int>(i);
    }
    return '?';
}

}

const Font& GetDefaultFont() {
    // Lusta betöltés: a static változó csak az első hívásnál jön létre,
    // amikor a Metal eszköz (a Window) már biztosan létezik
    static Font font;
    static bool loaded = false;
    if (loaded) return font;
    loaded = true;

    for (const auto& glyph : Internal::kDefaultFontExtra) {
        font.extraGlyphs.push_back(glyph.codepoint);
    }

    // 128 ASCII + az extra betűk, soronként 16 → 16 x 10 kocka, mindegyik 8 x 8 pixel
    const int glyphCount = 128 + static_cast<int>(font.extraGlyphs.size());
    const int rows   = (glyphCount + font.columns - 1) / font.columns;   // felfelé kerekítve
    const int width  = font.columns * font.glyphWidth;
    const int height = rows * font.glyphHeight;
    std::vector<uint8_t> pixels(width * height * 4, 0);   // 0 = minden átlátszó

    for (int g = 0; g < glyphCount; g++) {
        const uint8_t* bitmap = g < 128 ? Internal::kDefaultFont8x8[g]
                                        : Internal::kDefaultFontExtra[g - 128].rows;

        for (int row = 0; row < 8; row++) {
            for (int bit = 0; bit < 8; bit++) {
                if (((bitmap[row] >> bit) & 1) == 0) continue;

                int x = (g % font.columns) * font.glyphWidth + bit;
                int y = (g / font.columns) * font.glyphHeight + row;
                size_t i = (static_cast<size_t>(y) * width + x) * 4;

                // Fehér: így a DrawText color paramétere bármilyen színre színezheti
                pixels[i + 0] = 255;
                pixels[i + 1] = 255;
                pixels[i + 2] = 255;
                pixels[i + 3] = 255;
            }
        }
    }

    font.texture = LoadTextureFromPixels(pixels.data(), width, height);
    return font;
}

void DrawText(const char* text, Vector2 position, float fontSize, const Color& color) {
    DrawTextEx(GetDefaultFont(), text, position, fontSize, 0.0f, color);
}

void DrawText(const std::string& text, Vector2 position, float fontSize, const Color& color) {
    DrawTextEx(GetDefaultFont(), text.c_str(), position, fontSize, 0.0f, color);
}

void DrawTextEx(const Font& font, const std::string& text, Vector2 position, float fontSize, float spacing, const Color& color) {
    DrawTextEx(font, text.c_str(), position, fontSize, spacing, color);
}

void DrawTextEx(const Font& font, const char* text, Vector2 position, float fontSize, float spacing, const Color& color) {
    if (!text || font.texture.id == 0) return;

    position = SnapToPixel(position);

    float scale  = fontSize / static_cast<float>(font.glyphHeight);
    float glyphW = static_cast<float>(font.glyphWidth);
    float glyphH = static_cast<float>(font.glyphHeight);
    Vector2 cursor = position;

    const char* p = text;
    while (*p) {
        uint32_t codepoint = NextCodepoint(p);

        if (codepoint == '\n') {
            cursor.x = position.x;
            cursor.y += fontSize;
            continue;
        }

        // A szóköznek nincs képe, csak továbblépünk
        if (codepoint != ' ') {
            int index = GlyphIndex(font, codepoint);
            float sx = static_cast<float>(index % font.columns) * glyphW;
            float sy = static_cast<float>(index / font.columns) * glyphH;

            DrawTexturePro(font.texture,
                           Rect(sx, sy, glyphW, glyphH),
                           Rect(cursor, glyphW * scale, glyphH * scale),
                           Vector2(0.0f, 0.0f), 0.0f, color);
        }

        cursor.x += glyphW * scale + spacing;
    }
}

void DrawFPS(Vector2 position) {
    int fps = GetFPS();

    Color color(0, 228, 48);                     // zöld
    if (fps < 30) color = Color(255, 161, 0);    // narancs
    if (fps < 15) color = Color(230, 41, 55);    // piros

    DrawText(std::to_string(fps) + " FPS", position, 16.0f, color);
}

Vector2 MeasureText(const char* text, float fontSize) {
    return MeasureTextEx(GetDefaultFont(), text, fontSize, 0.0f);
}

Vector2 MeasureText(const std::string& text, float fontSize) {
    return MeasureTextEx(GetDefaultFont(), text.c_str(), fontSize, 0.0f);
}

Vector2 MeasureTextEx(const Font& font, const std::string& text, float fontSize, float spacing) {
    return MeasureTextEx(font, text.c_str(), fontSize, spacing);
}

Vector2 MeasureTextEx(const Font& font, const char* text, float fontSize, float spacing) {
    if (!text || !*text) return Vector2(0.0f, 0.0f);

    float advance = static_cast<float>(font.glyphWidth) * (fontSize / static_cast<float>(font.glyphHeight)) + spacing;
    float lineWidth = 0.0f;
    float maxWidth  = 0.0f;
    int lines = 1;

    // Karakterenként lépünk, nem bájtonként: az 'á' 2 bájt, de csak 1 betű széles
    const char* p = text;
    while (*p) {
        if (NextCodepoint(p) == '\n') {
            maxWidth = std::max(maxWidth, lineWidth);
            lineWidth = 0.0f;
            lines++;
            continue;
        }
        lineWidth += advance;
    }
    maxWidth = std::max(maxWidth, lineWidth);

    // Az utolsó betű utáni térköz nem része a szövegnek
    if (maxWidth > 0.0f) maxWidth -= spacing;

    return Vector2(maxWidth, static_cast<float>(lines) * fontSize);
}

}
