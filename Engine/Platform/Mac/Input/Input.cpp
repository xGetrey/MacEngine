//
//  Input.cpp
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 28..
//

#include "Input.h"

namespace {
constexpr int KeyCount = static_cast<int>(Engine::Key::Count);

bool s_Keys[KeyCount] = {};
bool sPrevKeys[KeyCount] = {};

int ToIndex(Engine::Key key) { return static_cast<int>(key); }

}

namespace Engine {

bool IsKeyDown(Key key) {
    
}

}
