//
//  MenuItemData.cpp
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 27..
//

#include "MenuItemData.h"
#include "../Section/MenuData.h"

#include <string>
#include <functional>

Engine::MenuItems::MenuItemData& Engine::MenuItems::MenuItemData::shortcut(std::string shortcut) {
    shortc = shortcut;
    return *this;
}

Engine::MenuItems::MenuItemData& Engine::MenuItems::MenuItemData::onClick(std::function<void()> func) {
    onclick = func;
    return *this;
}
/*
Engine::MenuItems::MenuItemData& Engine::MenuItems::MenuItemData::separate() {
    isSeparator = true;
    return *this;
}

Engine::MenuItems::MenuItemData& Engine::MenuItems::MenuItemData::end(Engine::MenuItems::MenuData& section) {
    section.AddMenuItem(*this);
    return *this;
}
 */
