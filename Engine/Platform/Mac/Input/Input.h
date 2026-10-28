//
//  Input.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 28..
//

#pragma once

#include "KeyCodes.h"

namespace Engine {

bool IsKeyDown(Key key);
bool IsKeyPressed(Key key);
bool IsKeyReleased(Key key);

bool IsMouseButtonDown(Key key);
bool IsMouseButtonPressed(Key key);
bool IsMouseButtonReleased(Key key);

float GetMouseX();
float GetMouseY();
float GetMouseDeltaX();
float GetMouseDeltaY();
float GetMousePos();
float GetScrollY();

namespace Internal {
void Input_BeginFrame();
void Input_SetKey(Key key, bool down);
void Input_SetMouseButton(MouseButton button, bool down);
void Input_SetMousePosition(float x, float y);
void Input_AddScroll(float x, float y);
void Input_ClearAll();

} // Intrenal namespace
} // Engine namespace
