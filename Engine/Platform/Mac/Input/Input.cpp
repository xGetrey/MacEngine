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

bool s_Keys[KeyCount] = {};
bool sPrevKeys[KeyCount] = {};

int ToIndex(Engine::Key key) { return static_cast<int>(key); }
bool IsValid(int i) {return  i > 0 && i < KeyCount;}

}

namespace Engine {

bool IsKeyDown(Key key) {
    int i = ToIndex(key);
    if (!IsValid(i)) return false;
    return s_Keys[i];
}

bool IsKeyPressed(Key key) {
    int i = ToIndex(key);
    if (!IsValid(i)) return false;
    return s_Keys[i] && !sPrevKeys[i];
}

bool IsKeyReleased(Key key) {
    int i = ToIndex(key);
    if (!IsValid(i)) return false;
    return !s_Keys[i] && sPrevKeys[i];
}

namespace Internal {
void Input_BeginFrame() {
    std::copy(s_Keys, s_Keys + KeyCount, sPrevKeys);
}

void Input_SetKey(Key key, bool down) {
    int i = ToIndex(key);
    if (!IsValid(i)) return;
    s_Keys[i] = down;
}

void Input_ClearAll() {
    std::fill(s_Keys, s_Keys + KeyCount, false);
    std::fill(sPrevKeys, sPrevKeys + KeyCount, false);
}

} // Internal namespace
}
