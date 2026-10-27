//
//  MenuData.cpp
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 27..
//

#include "Menubar.h"

void Engine::MenuItems::MenuData::end() {
    Engine::Menubar::Get().AddMenu(*this);
}
