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
    
    /*
    Engine::MenuItems::MenuData teszt0 = Engine::MenubarApi::menuSection("Teszt");
    Engine::MenubarApi::menuItem("teszt").onClick(teszt).shortcut("b").end(teszt0);
    Engine::MenubarApi::menuItem("").separate().end(teszt0);
    Engine::MenubarApi::menuItem("teszt").onClick(teszt).end(teszt0);
    Engine::MenubarApi::menuItem("teszt").onClick(teszt).shortcut("e").end(teszt0);
    Engine::MenubarApi::menuItem("teszt").onClick(teszt).end(teszt0);
    Engine::MenubarApi::menuItem("teszt").onClick(teszt).end(teszt0);
    Engine::MenubarApi::menuItem("teszt").onClick(teszt).end(teszt0);
    Engine::MenubarApi::menuItem("teszt").onClick(teszt).end(teszt0);
    teszt0.end();
    
    Engine::MenuItems::MenuData tesztt1 = Engine::MenubarApi::menuSection("Teszt");
    Engine::MenuItems::MenuData tesztt2 = Engine::MenubarApi::menuSection("Teszt");
    Engine::MenuItems::MenuData tesztt3 = Engine::MenubarApi::menuSection("Teszt");
    Engine::MenuItems::MenuData tesztt4 = Engine::MenubarApi::menuSection("Teszt");
    Engine::MenuItems::MenuData tesztt5 = Engine::MenubarApi::menuSection("Teszt");
    Engine::MenuItems::MenuData tesztt6 = Engine::MenubarApi::menuSection("Teszt");
    Engine::MenuItems::MenuData tesztt7 = Engine::MenubarApi::menuSection("Teszt");
    Engine::MenubarApi::menuItem("teszt").onClick(teszt).end(tesztt1);
    Engine::MenubarApi::menuItem("teszt").onClick(teszt).end(tesztt2);
    Engine::MenubarApi::menuItem("teszt").onClick(teszt).end(tesztt3);
    Engine::MenubarApi::menuItem("teszt").onClick(teszt).end(tesztt4);
    Engine::MenubarApi::menuItem("teszt").onClick(teszt).end(tesztt5);
    Engine::MenubarApi::menuItem("teszt").onClick(teszt).end(tesztt6);
    Engine::MenubarApi::menuItem("teszt").onClick(teszt).end(tesztt7);
    tesztt1.end();
    tesztt2.end();
    tesztt3.end();
    tesztt4.end();
    tesztt5.end();
    tesztt6.end();
    tesztt7.end();
    Engine::MenubarApi::BuildMenubar();*/
    
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
