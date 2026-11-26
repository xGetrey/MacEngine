//
//  Input.cpp
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 28..
//

#include "Input.h"
#include <algorithm>

namespace {
constexpr int KeyCount = static_cast<int>(Engine::Key::Count);
constexpr int MouseCount = static_cast<int>(Engine::MouseButton::Count);

bool s_Keys[KeyCount] = {};
bool sPrevKeys[KeyCount] = {};

// Ugyanez fizikai hely szerint (amerikai kiosztás), a kiosztástól függetlenül
bool s_PhysicalKeys[KeyCount] = {};
bool sPrevPhysicalKeys[KeyCount] = {};

bool s_Mouses[MouseCount] = {};
bool sPrevMouses[MouseCount] = {};

Engine::Vector2 s_MousePos = Engine::Vector2(0, 0);
Engine::Vector2 s_MouseDelta = Engine::Vector2(0, 0);
Engine::Vector2 s_Scroll = Engine::Vector2(0, 0);

int ToIndexKey(Engine::Key key) { return static_cast<int>(key); }
bool IsValidKey(int i) {return  i > 0 && i < KeyCount;}   // a 0 az Unknown

int ToIndexMouse(Engine::MouseButton button) { return static_cast<int>(button); }
bool IsValidMouse(int i) { return i >= 0 && i < MouseCount; }   // a 0 a Left, az is érvényes

}

namespace Engine {

bool IsKeyDown(Key key) {
    int i = ToIndexKey(key);
    if (!IsValidKey(i)) return false;
    return s_Keys[i];
}

bool IsKeyPressed(Key key) {
    int i = ToIndexKey(key);
    if (!IsValidKey(i)) return false;
    return s_Keys[i] && !sPrevKeys[i];
}

bool IsKeyReleased(Key key) {
    int i = ToIndexKey(key);
    if (!IsValidKey(i)) return false;
    return !s_Keys[i] && sPrevKeys[i];
}

bool IsPhysicalKeyDown(Key key) {
    int i = ToIndexKey(key);
    if (!IsValidKey(i)) return false;
    return s_PhysicalKeys[i];
}

bool IsPhysicalKeyPressed(Key key) {
    int i = ToIndexKey(key);
    if (!IsValidKey(i)) return false;
    return s_PhysicalKeys[i] && !sPrevPhysicalKeys[i];
}

bool IsPhysicalKeyReleased(Key key) {
    int i = ToIndexKey(key);
    if (!IsValidKey(i)) return false;
    return !s_PhysicalKeys[i] && sPrevPhysicalKeys[i];
}

bool IsMouseButtonDown(MouseButton button) {
    int i = ToIndexMouse(button);
    if (!IsValidMouse(i)) return false;
    return s_Mouses[i];
}

bool IsMouseButtonPressed(MouseButton button) {
    int i = ToIndexMouse(button);
    if (!IsValidMouse(i)) return false;
    return s_Mouses[i] && !sPrevMouses[i];
}

bool IsMouseButtonReleased(MouseButton button) {
    int i = ToIndexMouse(button);
    if (!IsValidMouse(i)) return false;
    return !s_Mouses[i] && sPrevMouses[i];
}

float GetMouseX() { return s_MousePos.x; }
float GetMouseY() { return s_MousePos.y; }
float GetMouseDeltaX() { return s_MouseDelta.x; }
float GetMouseDeltaY() { return s_MouseDelta.y; }
Vector2 GetMousePos() { return s_MousePos; }
float GetScrollX() { return s_Scroll.x; }
float GetScrollY() { return s_Scroll.y; }

namespace Internal {
void Input_BeginFrame() {
    std::copy(s_Keys, s_Keys + KeyCount, sPrevKeys);
    std::copy(s_PhysicalKeys, s_PhysicalKeys + KeyCount, sPrevPhysicalKeys);
    std::copy(s_Mouses, s_Mouses + MouseCount, sPrevMouses);

    s_MouseDelta = Vector2(0, 0);
    s_Scroll = Vector2(0, 0);
}

void Input_SetKey(Key key, bool down) {
    int i = ToIndexKey(key);
    if (!IsValidKey(i)) return;
    s_Keys[i] = down;
}

void Input_SetPhysicalKey(Key key, bool down) {
    int i = ToIndexKey(key);
    if (!IsValidKey(i)) return;
    s_PhysicalKeys[i] = down;
}

void Input_SetMouseButton(MouseButton button, bool down) {
    int i = ToIndexMouse(button);
    if (!IsValidMouse(i)) return;
    s_Mouses[i] = down;
}

void Input_SetMousePosition(float x, float y) {
    s_MousePos.x = x;
    s_MousePos.y = y;
}

void Input_AddMouseDelta(float dx, float dy) {
    s_MouseDelta.x += dx;
    s_MouseDelta.y += dy;
}

void Input_AddScroll(float x, float y) {
    s_Scroll.x += x;
    s_Scroll.y += y;
}

void Input_ClearAll() {
    std::fill(s_Keys, s_Keys + KeyCount, false);
    std::fill(sPrevKeys, sPrevKeys + KeyCount, false);
    std::fill(s_PhysicalKeys, s_PhysicalKeys + KeyCount, false);
    std::fill(sPrevPhysicalKeys, sPrevPhysicalKeys + KeyCount, false);

    std::fill(s_Mouses, s_Mouses + MouseCount, false);
    std::fill(sPrevMouses, sPrevMouses + MouseCount, false);

    s_MouseDelta = Vector2(0, 0);
    s_Scroll = Vector2(0, 0);
}

} // Internal namespace
}
