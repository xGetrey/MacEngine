//
//  MenuData.cpp
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 27..
//

#include "../Item/MenuItemData.h"
#include "../Section/MenuData.h"
#include "../Menu/Menubar.h"

Engine::MenuItems::MenuData& Engine::MenuItems::MenuData::registerMenu() {
    Engine::MenuItems::Menubar::Get().AddMenu(*this);
    return *this;
}

Engine::MenuItems::MenuData& Engine::MenuItems::MenuData::Item(Engine::MenuItems::MenuItemData item) {
    items.push_back(item);
    return *this;
}

Engine::MenuItems::MenuData& Engine::MenuItems::MenuData::Separator() {
    MenuItemData sep = MenuItemData();
    sep.isSeparator = true;
    items.push_back(sep);
    return *this;
}
