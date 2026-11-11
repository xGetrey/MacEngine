//
//  main.cpp
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 25..
//

#include "Engine/MacEngine.h"
#include <iostream>

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
    
    std::cout << std::boolalpha;

    std::cout << Engine::DisplayMetrics.GetWidth() << std::endl;
    std::cout << Engine::DisplayMetrics.GetDisplayHz() << std::endl;
    std::cout << Engine::DisplayMetrics.isHDRSupported();
    
    Engine::Rect rect = Engine::Rect(Engine::Vector2(30.0f, 30.0f), 120.0f, 100.0f);
    //Engine::SetTargetFps(15);
    
    while (!window.ShouldClose()) {
        window.PollEvents();
        //std::cout << Engine::GetWidth() << " " << Engine::GetHeight() << std::endl;
        //std::cout << Engine::GetMousePos().x << std::endl;
        
        
        
        //Engine::DrawRect(rect, Engine::Color(120, 32, 0));
        Engine::DrawRectLines(rect, Engine::Color(255, 32, 0), 20);
        Engine::DrawCircle(Engine::Vector2(Engine::GetWidth()/2, Engine::GetHeight()/2), 5.0f, Engine::Color(255, 255, 0));
        Engine::DrawRoundedLine(Engine::Vector2(Engine::GetWidth()/2, Engine::GetHeight()/2), Engine::GetMousePos(), Engine::Color(0, 0, 0, 255), 20);
        
        if (Engine::IsKeyDown(Engine::Key::D)) {
            rect.pos.x += 100.0f * Engine::GetDeltaTime();
        }
        if (Engine::IsKeyDown(Engine::Key::A)) {
            rect.pos.x -= 100.0f * Engine::GetDeltaTime();
        }
        if (Engine::IsKeyDown(Engine::Key::W)) {
            rect.pos.y -= 100.0f * Engine::GetDeltaTime();
        }
        if (Engine::IsKeyDown(Engine::Key::S)) {
            rect.pos.y += 100.0f * Engine::GetDeltaTime();
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
        Engine::Present();
    }
    
    return 0;
}
