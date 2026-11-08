//
//  Time.cpp
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 08..
//

#include "Time.h"
#include <chrono>
#include "../../Platform/Mac/Display/DisplayMetrics.h"
#include <thread>

namespace {
using Clock = std::chrono::steady_clock;

Clock::time_point s_LastFrame;
float s_DeltaTime = 0.0f;

int s_TargetFPS = 0;
Clock::time_point s_NextFrame;

}

namespace Engine {
float GetDeltaTime() {
    return s_DeltaTime;
}

void SetTargetFps(int fps) {
    if (fps < 10) {s_TargetFPS = 10;} else {s_TargetFPS = fps;}
    s_NextFrame = Clock::now();
}

namespace Internal {
void Time_Init() {
    s_LastFrame = Clock::now();
    s_NextFrame = s_LastFrame;
}

void Time_BeginFrame() {
    // 1. Várakozás, ha van FPS-korlát
    if (s_TargetFPS > 0) {
        auto frameDuration = std::chrono::duration_cast<Clock::duration>(
            std::chrono::duration<double>(1.0 / s_TargetFPS));

        s_NextFrame += frameDuration;

        if (Clock::now() > s_NextFrame) {
            s_NextFrame = Clock::now();
        } else {
            std::this_thread::sleep_until(s_NextFrame - std::chrono::milliseconds(1));
            // A maradék pontos kivárása
            while (Clock::now() < s_NextFrame) { }
        }
    }

    auto now = Clock::now();
    s_DeltaTime = std::chrono::duration<float>(now - s_LastFrame).count();
    s_LastFrame = now;

    if (s_DeltaTime > 0.1f) s_DeltaTime = 0.1f;
}

}
}
