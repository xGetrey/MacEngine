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
    
    std::cout << std::boolalpha;
    
    std::cout << Engine::DisplayMetrics.GetWidth() << std::endl;
    std::cout << Engine::DisplayMetrics.GetDisplayHz() << std::endl;
    std::cout << Engine::DisplayMetrics.isHDRSupported();
    
    /*std::cout << Engine::Display::DisplayMetrics::GetScaleFactor() << std::endl;
    std::cout << Engine::Display::DisplayMetrics::GetWidth() << std::endl;
    std::cout << Engine::Display::DisplayMetrics::GetHeight() << std::endl;
    std::cout << Engine::Display::DisplayMetrics::GetVisibleWidth() << std::endl;
    std::cout << Engine::Display::DisplayMetrics::GetVisibleHeight() << std::endl;
    std::cout << Engine::Display::DisplayMetrics::GetDisplayID() << std::endl;*/
    
    while (!window.ShouldClose()) {
        window.PollEvents();
        //std::cout << Engine::GetWidth() << " " << Engine::GetHeight() << std::endl;
    }
    
    return 0;
}
