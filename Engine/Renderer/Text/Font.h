//
//  Font.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 15..
//
//  Szövegkirajzolás bitmap fonttal.
//
//  Gyors példa:
//      DrawText("Hello MacEngine!", {20, 20}, 32, {255, 255, 255, 255});
//      DrawText(std::format("Pont: {}", score), {20, 60}, 16, {255, 200, 0, 255});
//      DrawFPS({10, 10});
//
//  Tudnivalók:
//  - A szöveg UTF-8 (a C++ string literálok alapból azok), az ékezetes betűk működnek.
//  - Amelyik betű nincs a fontban, az '?'-ként jelenik meg.
//  - A beépített font 8x8 pixeles: a 8 többszörösei (8, 16, 24, 32...) méretek lesznek
//    egyenletesek, más méreteknél egyes pixelsorok vastagabbak lesznek.
//  - A kezdőpozíciót a képernyő valódi pixeleihez igazítjuk (Retinán fél pontokhoz is),
//    hogy a betűk tört koordinátán se legyenek elmosódottak vagy egyenetlenek.
//  - Számokat, változókat a std::format-tal (#include <format>) lehet a szövegbe tenni:
//        std::format("HP: {}/{}", hp, maxHp)      std::format("{:.1f} s", time)
//

#pragma once

#include "../Texture/Texture.h"
#include <string>
#include <vector>

namespace Engine {

// Bitmap font: a betűk egyforma kockákban, rácsban vannak a textúrán.
// A 0–127. kocka az ASCII karakterek (a kocka száma = a karakter kódja),
// utána jönnek az extraGlyphs-ben felsorolt betűk.
struct Font {
    Texture texture;
    int glyphWidth  = 8;    // egy kocka szélessége a textúrán, pixelben
    int glyphHeight = 8;    // egy kocka magassága a textúrán, pixelben
    int columns     = 16;   // hány kocka van egy sorban a textúrán

    // Az ASCII utáni (128., 129., ...) kockákban lévő betűk Unicode-kódja, pl. 0x00E1 = 'á'
    std::vector<uint32_t> extraGlyphs;
};

// A beépített 8x8-as font (ASCII + magyar ékezetes betűk).
// Az első hívásnál készül el, ezért csak a Window létrehozása után hívd.
const Font& GetDefaultFont();

// --- Kirajzolás -----------------------------------------------------------

// Szöveg a beépített fonttal.
//   position: a szöveg bal felső sarka
//   fontSize: a betűk magassága pixelben
//   '\n': új sor, ami fontSize-zal lejjebb kezdődik
void DrawText(const char* text, Vector2 position, float fontSize, const Color& color);
void DrawText(const std::string& text, Vector2 position, float fontSize, const Color& color);

// Szöveg tetszőleges fonttal.
//   spacing: plusz távolság a betűk között pixelben (0 = a font saját térköze, negatív = szorosabb)
void DrawTextEx(const Font& font, const char* text, Vector2 position, float fontSize, float spacing, const Color& color);
void DrawTextEx(const Font& font, const std::string& text, Vector2 position, float fontSize, float spacing, const Color& color);

// Kiírja az aktuális FPS-t (pl. "60 FPS"), 16-os méretben.
// Színe: zöld, 30 alatt narancs, 15 alatt piros.
void DrawFPS(Vector2 position);

// --- Méretezés ------------------------------------------------------------

// Milyen széles és magas lenne a kirajzolt szöveg pixelben. Középre igazítás:
//     Vector2 size = MeasureText(title, 64);
//     DrawText(title, {(GetWidth() - size.x) / 2, 100}, 64, color);
Vector2 MeasureText(const char* text, float fontSize);
Vector2 MeasureText(const std::string& text, float fontSize);
Vector2 MeasureTextEx(const Font& font, const char* text, float fontSize, float spacing);
Vector2 MeasureTextEx(const Font& font, const std::string& text, float fontSize, float spacing);

}
