//
//  MacKeyMap.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 04..
//

#pragma once
#include "../../../Core/Input/KeyCodes.h"

namespace Engine {
Key TranslateKey(unsigned short code);
bool IsModifierDown(unsigned short code, unsigned long flags);
void RebuildLayoutTable();
Key TranslateLogicalKey(unsigned short code);
// KeyDown/KeyUp eseményekhez: megjegyzik, melyik keyCode melyik Key-t nyomta le
Key LogicalKeyDown(unsigned short code);
Key LogicalKeyUp(unsigned short code);
void ClearPressedKeys();
}
