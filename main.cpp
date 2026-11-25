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
    Vector2 vector2 = Vector2(300.0f, 300.0f);
    Vector2 vector3 = Vector2(0.0f, 0.0f);
    
    Rect rect1 = Rect(vector1, 120.0f, 200.0f);
    Rect rect2 = Rect(vector2, 120.0f, 200.0f);
    
    Color green = Color(0, 255, 0, 255);
    Color red = Color(255, 0, 0, 255);
    
    while (!window.ShouldClose()) {
        window.PollEvents();
        //rect1.moveTo({600.0f, 600.0f}, 100.0f);
        if (IsKeyDown(Key::D)) {
            vector3.x += 300.0f * GetDeltaTime();
        }
        if (IsKeyDown(Key::A)) {
            vector3.x -= 300.0f * GetDeltaTime();
        }
        if (IsKeyDown(Key::S)) {
            vector3.y += 300.0f * GetDeltaTime();
        }
        if (IsKeyDown(Key::W)) {
            vector3.y -= 300.0f * GetDeltaTime();
        }
        
        if (IsKeyPressed(Key::Z)) {
            std::cout << "Z" << std::endl;
        }
        
        BeginDraw();
        
        DrawCircle(vector3, 5.0f, Color(255, 255, 255));
        if (rect2.intersects(rect1) || rect2.contains(vector3) || rect2.contains(GetMousePos())) {
            DrawRect(rect2, red);
        } else {
            DrawRect(rect2, green);
        }
        DrawRect(rect1, {0, 0, 0, 255});
        
        EndDraw();
    }
    
    return 0;
}
