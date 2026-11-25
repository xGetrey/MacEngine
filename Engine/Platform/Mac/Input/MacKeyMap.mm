//
//  MacKeyMap.mm
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 28..
//

#include <Carbon/Carbon.h>
#include "KeyCodes.h"
#include <iostream>
#include <IOKit/hidsystem/IOLLEvent.h>

namespace Engine {
Key TranslateKey(unsigned short code) {
    switch (code) {
        case kVK_ANSI_A: return Engine::Key::A;
        case kVK_ANSI_B: return Engine::Key::B;
        case kVK_ANSI_C: return Engine::Key::C;
        case kVK_ANSI_D: return Engine::Key::D;
        case kVK_ANSI_E: return Engine::Key::E;
        case kVK_ANSI_F: return Engine::Key::F;
        case kVK_ANSI_G: return Engine::Key::G;
        case kVK_ANSI_H: return Engine::Key::H;
        case kVK_ANSI_I: return Engine::Key::I;
        case kVK_ANSI_J: return Engine::Key::J;
        case kVK_ANSI_K: return Engine::Key::K;
        case kVK_ANSI_L: return Engine::Key::L;
        case kVK_ANSI_M: return Engine::Key::M;
        case kVK_ANSI_N: return Engine::Key::N;
        case kVK_ANSI_O: return Engine::Key::O;
        case kVK_ANSI_P: return Engine::Key::P;
        case kVK_ANSI_Q: return Engine::Key::Q;
        case kVK_ANSI_S: return Engine::Key::S;
        case kVK_ANSI_T: return Engine::Key::T;
        case kVK_ANSI_R: return Engine::Key::R;
        case kVK_ANSI_U: return Engine::Key::U;
        case kVK_ANSI_V: return Engine::Key::V;
        case kVK_ANSI_W: return Engine::Key::W;
        case kVK_ANSI_X: return Engine::Key::X;
        case kVK_ANSI_Y: return Engine::Key::Y;
        case kVK_ANSI_Z: return Engine::Key::Z;
        
        case kVK_ANSI_0: return Engine::Key::Num0;
        case kVK_ANSI_1: return Engine::Key::Num1;
        case kVK_ANSI_2: return Engine::Key::Num2;
        case kVK_ANSI_3: return Engine::Key::Num3;
        case kVK_ANSI_4: return Engine::Key::Num4;
        case kVK_ANSI_5: return Engine::Key::Num5;
        case kVK_ANSI_6: return Engine::Key::Num6;
        case kVK_ANSI_7: return Engine::Key::Num7;
        case kVK_ANSI_8: return Engine::Key::Num8;
        case kVK_ANSI_9: return Engine::Key::Num9;
            
        case kVK_Space: return Engine::Key::Space;
        case kVK_Return: return Engine::Key::Enter;
        case kVK_Tab: return Engine::Key::Tab;
        case kVK_Delete: return Engine::Key::Backspace;
        case kVK_Escape: return Engine::Key::Escape;
            
        case kVK_RightArrow: return Engine::Key::Right;
        case kVK_LeftArrow: return Engine::Key::Left;
        case kVK_UpArrow: return Engine::Key::Up;
        case kVK_DownArrow: return Engine::Key::Down;
            
        case kVK_RightShift: return Engine::Key::RightShift;
        case kVK_Shift: return Engine::Key::LeftShift;
        case kVK_RightControl: return Engine::Key::RightControl;
        case kVK_Control: return Engine::Key::LeftControl;
        case kVK_RightOption: return Engine::Key::RightOption;
        case kVK_Option: return Engine::Key::LeftOption;
        case kVK_RightCommand: return  Engine::Key::RightCommand;
        case kVK_Command: return Engine::Key::LeftCommand;
            
        case kVK_F1: return Engine::Key::F1;
        case kVK_F2: return Engine::Key::F2;
        case kVK_F3: return Engine::Key::F3;
        case kVK_F4: return Engine::Key::F4;
        case kVK_F5: return Engine::Key::F5;
        case kVK_F6: return Engine::Key::F6;
        case kVK_F7: return Engine::Key::F7;
        case kVK_F8: return Engine::Key::F8;
        case kVK_F9: return Engine::Key::F9;
        case kVK_F10: return Engine::Key::F10;
        case kVK_F11: return Engine::Key::F11;
        case kVK_F12: return Engine::Key::F12;

            
        default:
            #ifndef NDEBUG
            std::cout << "Unknown Input" << std::endl;
            #endif
            return Engine::Key::Unknown;
    }
}

bool IsModifierDown(unsigned short code, unsigned long flags) {
    switch (code) {
        case kVK_Shift:        return (flags & NX_DEVICELSHIFTKEYMASK) != 0;
        case kVK_RightShift:   return (flags & NX_DEVICERSHIFTKEYMASK) != 0;
        case kVK_Control:      return (flags & NX_DEVICELCTLKEYMASK) != 0;
        case kVK_RightControl: return (flags & NX_DEVICERCTLKEYMASK) != 0;
        case kVK_Option:       return (flags & NX_DEVICELALTKEYMASK) != 0;
        case kVK_RightOption:  return (flags & NX_DEVICERALTKEYMASK) != 0;
        case kVK_Command:      return (flags & NX_DEVICELCMDKEYMASK) != 0;
        case kVK_RightCommand: return (flags & NX_DEVICERCMDKEYMASK) != 0;
        default: return false;
    }
}
}
