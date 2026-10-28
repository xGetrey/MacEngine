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
    }
    
    return 0;
}
