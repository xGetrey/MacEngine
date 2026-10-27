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
// Forward declaration to break the circular include with MenuData.h
struct MenuData;

struct MenuItemData {
    std::string title;
    std::string shortc;
    std::function<void()> onclick;
    bool isSeparator = false;
    
    MenuItemData& shortcut(std::string shortcut);
    MenuItemData& onClick(std::function<void()> func);
    //MenuItemData& separate();
    //MenuItemData& end(Engine::MenuItems::MenuData& section);
    
    //MenuItemData(std::string title, std::string shortcut, std::function<void()> onClick, bool isSeparator) : title(title), shortcut(shortcut), onClick(onClick), isSeparator(isSeparator) {}
};
}
