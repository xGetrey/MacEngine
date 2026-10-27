//
//  MenuItems.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 27..
//

#pragma once

#include <string>
#include <vector>
#include <functional>
#include <iostream>

#include "Section/MenuData.h"
#include "Item/MenuItemData.h"
#include "Menu/Menubar.h"


namespace Engine {
namespace MenubarApi {

inline Engine::MenuItems::MenuData menuSection(std::string title) {
    Engine::MenuItems::MenuData section = Engine::MenuItems::MenuData();
    section.title = title;
    return section;
}

inline Engine::MenuItems::MenuItemData menuItem(std::string title) {
    Engine::MenuItems::MenuItemData item = Engine::MenuItems::MenuItemData();
    item.title = title;
    return item;
}

inline void BuildMenubar() {
    Engine::MenuItems::Menubar::Get().Build();
}

}
}
