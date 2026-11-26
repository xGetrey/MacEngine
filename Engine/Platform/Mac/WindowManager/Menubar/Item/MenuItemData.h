//
//  MenuItemData.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 27..
//

#pragma once

#include <string>
#include <functional>
namespace Engine::MenuItems {
struct MenuData;

struct MenuItemData {
    std::string title;
    std::string shortc;
    std::function<void()> onclick;
    bool isSeparator = false;
    
    MenuItemData& shortcut(std::string shortcut);
    MenuItemData& onClick(std::function<void()> func);
    
};
}
