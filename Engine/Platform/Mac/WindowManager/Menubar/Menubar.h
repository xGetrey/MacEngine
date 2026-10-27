//
//  Menubar.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 26..
//

#pragma once

#include <string>
#include <functional>
#include <vector>

namespace Engine {
namespace MenuItems {
struct MenuItemData {
    std::string title;
    std::string shortcut;
    std::function<void()> onClick;
    bool isSeparator = false;
    
    //MenuItemData(std::string title, std::string shortcut, std::function<void()> onClick, bool isSeparator) : title(title), shortcut(shortcut), onClick(onClick), isSeparator(isSeparator) {}
};

struct MenuData {
    std::string title;
    std::vector<MenuItemData> items;
    
    void end();
};
}

class Menubar {
public:
    void AddMenu(const MenuItems::MenuData& menu);
    void Build();
    static Menubar& Get();
    
private:
    std::vector<MenuItems::MenuData> m_Menus;
};
}


