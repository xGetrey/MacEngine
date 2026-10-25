//
//  main.cpp
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 25..
//

#include "Engine/MacEngine.hpp"

int main() {
    Engine::Window window(800, 600, "Működj");
    
    while (!window.ShouldClose()) {
        window.PollEvents();
    }
    
    return 0;
}
