//
//  MacKeyMap.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 11. 04..
//

#pragma once
#include "KeyCodes.h"

namespace Engine {
Key TranslateKey(unsigned short code);
bool IsModifierDown(unsigned short code, unsigned long flags);
void RebuildLayoutTable();
Key TranslateLogicalKey(unsigned short code);
}
