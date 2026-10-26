//
//  Menubar.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 26..
//

#include <string>
#include <functional>
#include <vector>

namespace Engine {

struct MenuItemData {
    std::string title;
    std::string shortcut;
    std::function<void()> onClick;
    bool isSeparator = false;
    
    MenuItemData(std::string title, std::string shortcut, std::function<void()> onClick, bool isSeparator) : title(title), shortcut(shortcut), onClick(onClick), isSeparator(isSeparator) {}
};

struct MenuData {
    std::string title;
    std::vector<MenuItemData> items;
    
    void AddItem(std::string title, std::function<void()> onClick, std::string shortcut, bool isSeparator) {
        items.push_back(MenuItemData(title, shortcut, onClick, isSeparator));
    }
};

class Menubar {
public:
    void AddMenu(const MenuData& menu);
    void Build();
    static Menubar& Get();
    
private:
    std::vector<MenuData> m_Menus;
};

}
