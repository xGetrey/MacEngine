//
//  Time.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 08..
//

#pragma once

namespace Engine {

float GetDeltaTime();
// Másodpercenkénti képkockák száma, fél másodpercenként frissítve (így olvasható, nem ugrál)
int GetFPS();
void SetTargetFps(int fps);
int GetTargetFps();   // a beállított FPS-korlát, 0 = nincs korlát (alapértelmezett)

namespace Internal {
void Time_Init();
void Time_BeginFrame();
}

}
