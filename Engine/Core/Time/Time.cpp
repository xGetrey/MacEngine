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

int s_FPS = 0;
int s_FrameCount = 0;
float s_FPSTimer = 0.0f;

}

namespace Engine {
float GetDeltaTime() {
    return s_DeltaTime;
}

int GetFPS() {
    return s_FPS;
}

void SetTargetFps(int fps) {
    if (fps < 10) {s_TargetFPS = 10;} else {s_TargetFPS = fps;}
    s_NextFrame = Clock::now();
}

int GetTargetFps() {
    return s_TargetFPS;
}

namespace Internal {
void Time_Init() {
    s_LastFrame = Clock::now();
    s_NextFrame = s_LastFrame;
}

void Time_BeginFrame() {
    if (s_TargetFPS > 0) {
        auto frameDuration = std::chrono::duration_cast<Clock::duration>(
            std::chrono::duration<double>(1.0 / s_TargetFPS));

        s_NextFrame += frameDuration;

        if (Clock::now() > s_NextFrame) {
            s_NextFrame = Clock::now();
        } else {
            std::this_thread::sleep_until(s_NextFrame - std::chrono::milliseconds(1));
            while (Clock::now() < s_NextFrame) { }
        }
    }

    auto now = Clock::now();
    s_DeltaTime = std::chrono::duration<float>(now - s_LastFrame).count();
    s_LastFrame = now;

    s_FrameCount++;
    s_FPSTimer += s_DeltaTime;
    if (s_FPSTimer >= 0.5f) {
        s_FPS = static_cast<int>(s_FrameCount / s_FPSTimer + 0.5f);
        s_FrameCount = 0;
        s_FPSTimer = 0.0f;
    }

    if (s_DeltaTime > 0.1f) s_DeltaTime = 0.1f;
}

}
}
