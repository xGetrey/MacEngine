//
//  main.cpp
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 23..
//

#include "Engine/MacEngine.h"

using namespace Engine;

int main() {
    Window window = Window(1200, 800, "Anyam");
    window.SetResizable(true);
    window.SetBackgroundColor({100, 100, 130, 255});
    
    Vector2 vector1 = Vector2(100.0f, 200.0f);
    Rect rect1 = Rect(vector1, 120.0f, 200.0f);
    
    while (!window.ShouldClose()) {
        window.PollEvents();
        
        //rect1.moveTo({600.0f, 600.0f}, 100.0f);
        
        if (IsKeyDown(Key::D)) {
            rect1.pos.x += 10.0f;
        }
        
        BeginDraw();
        DrawRect(rect1, {0, 0, 0, 255});
        EndDraw();
    }
    
    return 0;
}
