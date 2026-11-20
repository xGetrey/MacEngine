//
//  main.cpp
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 25..
//

#include "Engine/MacEngine.h"
#include <iostream>
#include <format>
#include <cmath>

void teszt() {
    std::cout << "Teszt" << std::endl;
}

int main() {
    Engine::Window window(800, 600, "Működj");
    
    window.SetBackgroundColor(Engine::Color(100.0f, 25.0f, 255.0f, 100.0f));
    window.SetResizable(true);
    window.SetMiniaturizable(true);
    
    Engine::MenubarApi::menuSection("Teszt")
        .Item(Engine::menuItem("Teszt").onClick(teszt))
        .Separator()
        .Item(Engine::menuItem("Teszt").onClick(teszt).shortcut("g"))
        .registerMenu();
    Engine::BuildMenubar();
    Engine::SetAntialiasing(8);
    
    std::cout << std::boolalpha;

    std::cout << Engine::DisplayMetrics.GetWidth() << std::endl;
    std::cout << Engine::DisplayMetrics.GetDisplayHz() << std::endl;
    std::cout << Engine::DisplayMetrics.isHDRSupported();
    
    Engine::Texture texture = Engine::LoadTexture("jungel_tree1.png");
    const float texW = static_cast<float>(texture.width);    // 96
    const float texH = static_cast<float>(texture.height);   // 146
    
    Engine::Rect rect = Engine::Rect(Engine::Vector2(30.0f, 30.0f), 120.0f, 100.0f);
    
    const Engine::Color white(255, 255, 255);
    const Engine::Color gray(170, 170, 170);
    const Engine::Color yellow(255, 220, 0);
    
    // Tesztoldalak: Tab-bal lehet váltani
    int page = 0;
    const char* pageNames[] = { "Alakzatok", "Textúrák", "Szöveg", "Kamera" };
    
    float rotate = 0.0f;
    float time = 0.0f;
    bool fpsLimit = false;
    
    Engine::Camera2D camera;
    Engine::Vector2 player(0.0f, 0.0f);
    
    // Kis felirat egy teszt alá
    auto label = [&](const char* text, float x, float y) {
        Engine::DrawText(text, {x, y}, 8, gray);
    };
    
    Engine::Vector2 vector1 = {20.0f, 20.0f};
    Engine::Vector2 vector2 = {24.0f, 45.0f};
    
    std::cout << (vector1 + vector2).toString() + " +" << std::endl;
    vector2 += vector1;
    std::cout << vector2.toString() << " +=" << std::endl;
    std::cout << (-vector2).toString() << " -" << std::endl;
    
    std::cout << (vector1 + vector2).negate().toString() + " negate()" << std::endl;
     
    
    Engine::Vector2 hihi = {32.0f, 32.0f};
    
    hihi += 3.0f;
    
    std::cout << "x: " << hihi.x << ", y: " << hihi.y << std::endl;
    
    hihi = hihi + 3.0f;
    
    std::cout << "x: " << hihi.x << ", y: " << hihi.y << std::endl;
    
    hihi = 3.0f + hihi;
    
    std::cout << "x: " << hihi.x << ", y: " << hihi.y << std::endl;
    
    
    while (!window.ShouldClose()) {
        window.PollEvents();
        
        float dt = Engine::GetDeltaTime();
        time += dt;
        rotate += 60.0f * dt;   // 60 fok / másodperc
        
        // --- Vezérlés ---------------------------------------------------
        if (Engine::IsKeyPressed(Engine::Key::Tab)) page = (page + 1) % 4;
        
        if (Engine::IsKeyPressed(Engine::Key::Num1)) Engine::SetAntialiasing(1);
        if (Engine::IsKeyPressed(Engine::Key::Num4)) Engine::SetAntialiasing(4);
        if (Engine::IsKeyPressed(Engine::Key::Num8)) Engine::SetAntialiasing(8);
        
        // GetFPS + GetTargetFps teszt: L = 30 FPS korlát ki/be (a "ki" itt 240-es korlát,
        // mert a SetTargetFps(0) jelenleg 10-re korlátozna)
        if (Engine::IsKeyPressed(Engine::Key::L)) {
            fpsLimit = !fpsLimit;
            Engine::SetTargetFps(fpsLimit ? 30 : 240);
        }
        
        Engine::BeginDraw();
        
        // --- 1. oldal: alakzatok ----------------------------------------
        if (page == 0) {
            if (Engine::IsKeyDown(Engine::Key::D)) rect.pos.x += 100.0f * dt;
            if (Engine::IsKeyDown(Engine::Key::A)) rect.pos.x -= 100.0f * dt;
            if (Engine::IsKeyDown(Engine::Key::W)) rect.pos.y -= 100.0f * dt;
            if (Engine::IsKeyDown(Engine::Key::S)) rect.pos.y += 100.0f * dt;
            
            Engine::Vector2 center(Engine::GetWidth() / 2.0f, Engine::GetHeight() / 2.0f);
            
            Engine::DrawRect(Engine::Rect(560, 80, 120, 60), Engine::Color(120, 32, 0));
            label("DrawRect", 560, 146);
            
            Engine::DrawRectLines(rect, Engine::Color(255, 32, 0), 20);
            label("DrawRectLines (WASD)", rect.pos.x, rect.pos.y + rect.height + 4);
            
            Engine::DrawCircle(center, 40.0f, Engine::Color(255, 255, 0));
            Engine::DrawRoundedLine(center, Engine::GetMousePos(), Engine::Color(0, 0, 0, 100), 20);
            label("DrawCircle + DrawRoundedLine (egér)", center.x - 140, center.y + 48);
            
            Engine::DrawLine({560, 200}, {700, 260}, white, 3);
            label("DrawLine", 560, 270);
            
            Engine::DrawPolygon({150.0f, 450.0f}, 70.0f, 6, {255, 25, 255, 255});
            label("DrawPolygon (6)", 90, 530);
            
            Engine::DrawSemicircle({400, 470}, 40.0f, rotate, white);
            label("DrawSemicircle (forog)", 330, 530);
        }
        
        // --- 2. oldal: textúrák -----------------------------------------
        if (page == 1) {
            // Első sor
            Engine::DrawTexture(texture, {30, 70}, white);
            label("DrawTexture", 30, 222);
            
            Engine::DrawTextureEx(texture, {160, 70}, 0.0f, 0.5f, white);
            label("Ex 0.5x", 160, 150);
            
            Engine::DrawTextureEx(texture, {250, 70}, 0.0f, 1.5f, white);
            label("Ex 1.5x", 250, 295);
            
            // A saját közepe körül forog: dest.pos = a közép, origin = a kép fele
            Engine::DrawTexturePro(texture, Engine::Rect(0, 0, texW, texH),
                                   Engine::Rect(500, 150, texW, texH),
                                   Engine::Vector2(texW / 2, texH / 2), rotate, white);
            label("Pro: forgás középen", 425, 245);
            
            // A bal felső sarka körül forog
            Engine::DrawTextureEx(texture, {680, 100}, rotate, 0.5f, white);
            label("Ex: forgás a sarok körül", 610, 245);
            
            // Második sor
            Engine::DrawTexturePro(texture, Engine::Rect(0, 0, -texW, texH),
                                   Engine::Rect(30, 330, texW, texH), {0, 0}, 0.0f, white);
            label("Pro: flipX", 30, 482);
            
            Engine::DrawTexturePro(texture, Engine::Rect(0, 0, texW, -texH),
                                   Engine::Rect(150, 330, texW, texH), {0, 0}, 0.0f, white);
            label("Pro: flipY", 150, 482);
            
            Engine::DrawTexturePro(texture, Engine::Rect(0, 0, texW, texH / 2),
                                   Engine::Rect(270, 330, texW, texH / 2), {0, 0}, 0.0f, white);
            label("Pro: felső fele", 270, 409);
            
            Engine::DrawTexturePro(texture, Engine::Rect(0, 0, texW, texH),
                                   Engine::Rect(390, 330, 200, 80), {0, 0}, 0.0f, white);
            label("Pro: nyújtva 200x80", 390, 416);
            
            Engine::DrawTexture(texture, {620, 330}, Engine::Color(255, 120, 120));
            Engine::DrawTexture(texture, {680, 380}, Engine::Color(255, 255, 255, 120));
            label("színezve / átlátszó", 620, 532);
        }
        
        // --- 3. oldal: szöveg -------------------------------------------
        if (page == 2) {
            // Méretek: a 8 többszörösei élesek, a 20 szándékosan nem az
            Engine::DrawText("8px",  {20, 60},  8,  white);
            Engine::DrawText("16px", {60, 60},  16, white);
            Engine::DrawText("24px", {140, 60}, 24, white);
            Engine::DrawText("32px", {250, 60}, 32, white);
            Engine::DrawText("20px (egyenetlen)", {400, 66}, 20, gray);
            
            // Ékezetek
            Engine::DrawText("Árvíztűrő tükörfúrógép", {20, 110}, 24, white);
            Engine::DrawText("ÁRVÍZTŰRŐ TÜKÖRFÚRÓGÉP", {20, 140}, 24, white);
            
            // Ismeretlen betűk → '?' (ß: 2 bájtos, ✓: 3 bájtos, emoji: 4 bájtos UTF-8)
            Engine::DrawText("Nincs a fontban: ß ✓ 🙂", {20, 175}, 16, gray);
            
            // Több sor
            Engine::DrawText("Első sor\nMásodik sor\nHarmadik", {20, 205}, 16, yellow);
            
            // std::format + std::string változat
            Engine::DrawText(std::format("Idő: {:.1f} s   Forgás: {:.0f}°", time, rotate),
                             {20, 265}, 16, white);
            
            // Betűköz (DrawTextEx)
            const Engine::Font& font = Engine::GetDefaultFont();
            Engine::DrawTextEx(font, "spacing = 4", {20, 295}, 16, 4.0f, white);
            Engine::DrawTextEx(font, "spacing = -2", {300, 295}, 16, -2.0f, white);
            
            // MeasureText: a keretnek pontosan a szöveg köré kell esnie, középre igazítva
            const char* title = "Középre igazítva";
            Engine::Vector2 size = Engine::MeasureText(title, 32);
            Engine::Vector2 pos((Engine::GetWidth() - size.x) / 2.0f, 340);
            Engine::DrawRectLines(Engine::Rect(pos, size.x, size.y), Engine::Color(255, 0, 0), 1);
            Engine::DrawText(title, pos, 32, white);
            
            Engine::Vector2 size2 = Engine::MeasureText("Két\nsoros szöveg", 16);
            Engine::DrawRectLines(Engine::Rect(Engine::Vector2(20, 400), size2.x, size2.y), Engine::Color(255, 0, 0), 1);
            Engine::DrawText("Két\nsoros szöveg", {20, 400}, 16, white);
            label("MeasureText: piros keret = mért méret", 20, 440);
            
            // Pixelre igazítás: lassan mozgó szöveg nem "hullámozhat"
            float x = 20.0f + (std::sin(time * 0.5f) + 1.0f) * 150.0f;
            Engine::DrawText("Lassan mozgó szöveg", {x, 480}, 16, white);
            label("tört koordinátán is egyenletes betűk kellenek", 20, 504);
            
            // Sok szöveg egyszerre (batch): az FPS ne essen le
            for (int i = 0; i < 8; i++) {
                for (int col = 0; col < 2; col++) {
                    Engine::DrawText("batch teszt batch teszt batch teszt batch teszt",
                                     {20.0f + col * 400.0f, 522.0f + i * 9.0f}, 8, Engine::Color(80, 80, 80));
                }
            }
        }
        
        // --- 4. oldal: kamera -------------------------------------------
        if (page == 3) {
            // A player a VILÁGBAN mozog, a kamera követi
            if (Engine::IsKeyDown(Engine::Key::D)) player.x += 300.0f * dt;
            if (Engine::IsKeyDown(Engine::Key::A)) player.x -= 300.0f * dt;
            if (Engine::IsKeyDown(Engine::Key::W)) player.y -= 300.0f * dt;
            if (Engine::IsKeyDown(Engine::Key::S)) player.y += 300.0f * dt;
            
            if (Engine::IsKeyDown(Engine::Key::E)) camera.zoom *= 1.0f + dt;   // közelít
            if (Engine::IsKeyDown(Engine::Key::Q)) camera.zoom *= 1.0f - dt;   // távolít
            if (Engine::IsKeyDown(Engine::Key::T)) camera.rotation += 45.0f * dt;
            if (Engine::IsKeyDown(Engine::Key::R)) camera.rotation -= 45.0f * dt;
            if (Engine::IsKeyPressed(Engine::Key::C)) { camera.zoom = 1.0f; camera.rotation = 0.0f; }
            
            camera.target = player;                                                       // ezt nézi
            camera.offset = { Engine::GetWidth() / 2.0f, Engine::GetHeight() / 2.0f };   // a képernyő közepén
            
            Engine::Vector2 mouseWorld = camera.ScreenToWorld(Engine::GetMousePos());
            
            Engine::BeginCamera(camera);
                // Sakktábla-padló: 20 x 20 kocka, -1000-től 1000-ig
                for (int gx = -10; gx < 10; gx++) {
                    for (int gy = -10; gy < 10; gy++) {
                        Engine::Color c = ((gx + gy) & 1) ? Engine::Color(40, 40, 60) : Engine::Color(60, 60, 90);
                        Engine::DrawRect(Engine::Rect(gx * 100.0f, gy * 100.0f, 100.0f, 100.0f), c);
                    }
                }
                
                // A világ (0,0) pontja
                Engine::DrawCircle({0, 0}, 12.0f, Engine::Color(255, 0, 0));
                Engine::DrawText("(0, 0)", {16, -8}, 16, white);
                
                // Fák a világban
                Engine::DrawTexture(texture, {300, -250}, white);
                Engine::DrawTexture(texture, {-500, 200}, white);
                
                // A player
                Engine::DrawRect(Engine::Rect(player.x - 16, player.y - 16, 32, 32), yellow);
                
                // Zöld pötty oda, ahol az egér a VILÁGBAN van
                Engine::DrawCircle(mouseWorld, 6.0f, Engine::Color(0, 255, 0));
            Engine::EndCamera();
            
            // --- UI: ez már nem mozog a kamerával ---
            Engine::DrawText(std::format("Player: {:.0f}, {:.0f}   Egér a világban: {:.0f}, {:.0f}",
                                         player.x, player.y, mouseWorld.x, mouseWorld.y), {10, 50}, 8, white);
            Engine::DrawText(std::format("Zoom: {:.2f}   Forgás: {:.0f} fok", camera.zoom, camera.rotation),
                             {10, 62}, 8, white);
            Engine::DrawText("WASD: mozgás   Q/E: zoom   R/T: forgatás   C: alaphelyzet", {10, 74}, 8, gray);
            
            // A WorldToScreen ellenőrzése: ez a zöld keret UI-ként, kézzel átváltva készül
            Engine::Vector2 o = camera.WorldToScreen({0, 0});
            Engine::DrawRectLines(Engine::Rect(o.x - 18, o.y - 18, 36, 36), Engine::Color(0, 255, 0), 2);
        }
        
        /*
        if (Engine::IsKeyPressed(Engine::Key::Space)) std::cout << Engine::GetDeltaTime();
        if (Engine::IsKeyPressed(Engine::Key::LeftShift))    std::cout << "Bal Shift LE" << std::endl;
        if (Engine::IsKeyReleased(Engine::Key::LeftShift))   std::cout << "Bal Shift FEL" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::RightShift))   std::cout << "Jobb Shift LE" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::RightOption))   std::cout << "Jobb Opt LE" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::LeftOption))   std::cout << "Bal Option LE" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::LeftCommand))  std::cout << "Bal Command LE" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::LeftControl))  std::cout << "Bal Control LE" << std::endl;
        
        if (Engine::IsMouseButtonPressed(Engine::MouseButton::Left)) std::cout << "Left" << std::endl;
        
        if (Engine::IsKeyPressed(Engine::Key::A)) std::cout << "A" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::B)) std::cout << "B" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::C)) std::cout << "C" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::D)) std::cout << "D" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::E)) std::cout << "E" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::F)) std::cout << "F" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::G)) std::cout << "G" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::H)) std::cout << "H" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::I)) std::cout << "I" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::J)) std::cout << "J" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::K)) std::cout << "K" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::L)) std::cout << "L" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::M)) std::cout << "M" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::N)) std::cout << "N" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::O)) std::cout << "O" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::P)) std::cout << "P" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::Q)) std::cout << "Q" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::S)) std::cout << "S" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::T)) std::cout << "T" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::R)) std::cout << "R" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::U)) std::cout << "U" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::V)) std::cout << "V" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::W)) std::cout << "W" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::X)) std::cout << "X" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::Y)) std::cout << "Y" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::Z)) std::cout << "Z" << std::endl;
        
        if (Engine::IsKeyPressed(Engine::Key::Num0)) std::cout << "0" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::Num1)) std::cout << "1" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::Num2)) std::cout << "2" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::Num3)) std::cout << "3" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::Num4)) std::cout << "4" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::Num5)) std::cout << "5" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::Num6)) std::cout << "6" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::Num7)) std::cout << "7" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::Num8)) std::cout << "8" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::Num9)) std::cout << "9" << std::endl;
        
        if (Engine::IsKeyPressed(Engine::Key::F1)) std::cout << "F1" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::F2)) std::cout << "F2" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::F3)) std::cout << "F3" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::F4)) std::cout << "F4" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::F5)) std::cout << "F5" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::F6)) std::cout << "F6" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::F7)) std::cout << "F7" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::F8)) std::cout << "F8" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::F9)) std::cout << "F9" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::F10)) std::cout << "F10" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::F11)) std::cout << "F11" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::F12)) std::cout << "F12" << std::endl;
        
        if (Engine::IsKeyPressed(Engine::Key::Backspace)) std::cout << "Backspace" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::Tab)) std::cout << "Tab" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::Space)) std::cout << "Space" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::Enter)) std::cout << "Enter" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::Escape)) std::cout << "Escape" << std::endl;
        
        if (Engine::IsKeyPressed(Engine::Key::Right)) std::cout << "Right" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::Left)) std::cout << "Left" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::Up)) std::cout << "Up" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::Down)) std::cout << "Down" << std::endl;
        
        if (Engine::IsKeyPressed(Engine::Key::LeftOption)) std::cout << "LeftCommand" << std::endl;
        if (Engine::IsKeyPressed(Engine::Key::RightCommand)) std::cout << "RightCommand" << std::endl;
        
        if (Engine::IsKeyReleased(Engine::Key::K)) std::cout << "K elengedve" << std::endl;
        */
        // --- Fejléc (minden oldalon): utoljára, hogy minden fölött legyen ---
        Engine::DrawText(std::format("[{}/4] {}", page + 1, pageNames[page]), {10, 10}, 16, yellow);
        Engine::DrawText(std::format("Tab: oldalváltás   1/4/8: AA ({}x)   L: FPS-korlát ({})",
                                     Engine::GetAntialiasing(), Engine::GetTargetFps()),
                         {10, 32}, 8, gray);
        Engine::DrawFPS({static_cast<float>(Engine::GetWidth()) - 80.0f, 10});
        
        Engine::EndDraw();
    }
    
    return 0;
}
