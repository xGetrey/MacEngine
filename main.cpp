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
    
    while (!window.ShouldClose()) {
        window.PollEvents();
        //std::cout << Engine::GetWidth() << " " << Engine::GetHeight() << std::endl;
        
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
    }
    
    return 0;
}
