//
//  Menubar.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 26..
//

#pragma once

#include "../Section/MenuData.h"

#include <string>
#include <functional>
#include <vector>


namespace Engine::MenuItems {

class Menubar {
public:
    void AddMenu(const MenuItems::MenuData& menu);
    void Build();
    static Menubar& Get();
    
private:
    std::vector<MenuItems::MenuData> m_Menus;
};

}
