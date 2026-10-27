//
//  MenuData.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 27..
//

#pragma once

#include <string>
#include <vector>

#include "../Item/MenuItemData.h"

namespace Engine::MenuItems {
struct MenuData {
    std::string title;
    std::vector<MenuItems::MenuItemData> items;
    
    MenuData& Item(MenuItems::MenuItemData item);
    MenuData& Separator();
    MenuData& registerMenu();
};
}
