//
//  MenuData.cpp
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 27..
//

#include "../Section/MenuData.h"
#include "../Menu/Menubar.h"

Engine::MenuItems::MenuData& Engine::MenuItems::MenuData::end() {
    Engine::MenuItems::Menubar::Get().AddMenu(*this);
    return *this;
}

void Engine::MenuItems::MenuData::AddMenuItem(Engine::MenuItems::MenuItemData item) {
    items.push_back(item);
}
