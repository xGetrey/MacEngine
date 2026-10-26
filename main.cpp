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
    
    Engine::MenuData file;
    Engine::MenuData tesztM;
    
    file.title = "File";
    file.AddItem("Menjen", teszt, "3", false);
    file.AddItem("Teszt teszt teszt", teszt, "", false);
    file.AddItem("Teszt teszt teszt", teszt, "w", true);
    file.AddItem("Teszt teszt teszt", teszt, "", false);
    file.AddItem("Teszt teszt teszt", teszt, "", false);
    file.AddItem("Teszt teszt teszt", teszt, "", true);
    file.AddItem("Teszt teszt teszt", teszt, "r", false);
    file.AddItem("Teszt teszt teszt", teszt, "", false);
    file.AddItem("Teszt teszt teszt", teszt, "", false);
    file.AddItem("Teszt teszt teszt", teszt, "", false);

    
    tesztM.title = "Teszt";
    tesztM.AddItem("Teszt teszt teszt", teszt, "", false);
    tesztM.AddItem("Teszt teszt teszt", teszt, "", false);
    tesztM.AddItem("Teszt teszt teszt", teszt, "", true);
    tesztM.AddItem("Teszt teszt teszt", teszt, "g", false);
    tesztM.AddItem("Teszt teszt teszt", teszt, "", false);
    tesztM.AddItem("Teszt teszt teszt", teszt, "", false);
    tesztM.AddItem("Teszt teszt teszt", teszt, "b", false);
    tesztM.AddItem("Teszt teszt teszt", teszt, "", true);
    tesztM.AddItem("Teszt teszt teszt", teszt, "", false);
    tesztM.AddItem("Teszt teszt teszt", teszt, "h", false);
    tesztM.AddItem("Teszt teszt teszt", teszt, "", false);
    tesztM.AddItem("Teszt teszt teszt", teszt, "", false);
    
    Engine::Menubar::Get().AddMenu(file);
    Engine::Menubar::Get().AddMenu(tesztM);
    
    Engine::Menubar::Get().Build();
    
    
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
