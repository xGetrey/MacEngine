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
#include "Menubar.h"
#include <iostream>


namespace Engine {
namespace MenubarApi {

inline Engine::MenuItems::MenuData menuSection(std::string title) {
    Engine::MenuItems::MenuData section = Engine::MenuItems::MenuData();
    section.title = title;
    return section;
}

inline void BuildMenubar() {
    Engine::Menubar::Get().Build();
}

}
}
