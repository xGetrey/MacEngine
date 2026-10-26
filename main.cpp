//
//  main.cpp
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 25..
//

#include "Engine/MacEngine.h"
#include <iostream>

int main() {
    Engine::Window window(800, 600, "Működj");
    
    window.SetBackgroundColor(Engine::Color(100.0f, 25.0f, 255.0f, 100.0f));
    window.SetResizable(true);

    
    while (!window.ShouldClose()) {
        window.PollEvents();
        std::cout << Engine::GetWidth() << " " << Engine::GetHeight() << std::endl;
    }
    
    return 0;
}
