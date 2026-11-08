//
//  Time.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 08..
//

#pragma once

namespace Engine {

float GetDeltaTime();
void SetTargetFps(int fps);
int GetTargetFps();

namespace Internal {
void Time_Init();
void Time_BeginFrame();
}

}
