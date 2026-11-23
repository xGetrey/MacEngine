//
//  Input.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 28..
//

#pragma once

#include "KeyCodes.h"
#include "../../../Core/Vector2/Vector2.h"

namespace Engine {

bool IsKeyDown(Key key);
bool IsKeyPressed(Key key);
bool IsKeyReleased(Key key);

bool IsMouseButtonDown(MouseButton button);
bool IsMouseButtonPressed(MouseButton button);
bool IsMouseButtonReleased(MouseButton button);

float GetMouseX();
float GetMouseY();
float GetMouseDeltaX();
float GetMouseDeltaY();
Engine::Vector2 GetMousePos();
float GetScrollX();
float GetScrollY();

namespace Internal {
void Input_BeginFrame();
void Input_SetKey(Key key, bool down);
void Input_SetMouseButton(MouseButton button, bool down);
void Input_SetMousePosition(float x, float y);
void Input_AddMouseDelta(float dx, float dy);
void Input_AddScroll(float x, float y);
void Input_ClearAll();

} // Intrenal namespace
} // Engine namespace
