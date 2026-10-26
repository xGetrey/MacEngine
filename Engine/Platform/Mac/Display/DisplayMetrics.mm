//
//  DisplayMetrics.mm
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 26..
//

#import "DisplayMetrics.h"
#import <Cocoa/Cocoa.h>
#include <string>

namespace Engine {
namespace Display {

int DisplayMetrics::GetWidth() {
    NSScreen* screen = [NSScreen mainScreen];
    return screen ? static_cast<int>(screen.frame.size.width) : 0;
}

int DisplayMetrics::GetHeight() {
    NSScreen* screen = [NSScreen mainScreen];
    return screen ? static_cast<int>(screen.frame.size.height) : 0;
}

int DisplayMetrics::GetVisibleWidth() {
    NSScreen* screen = [NSScreen mainScreen];
    return screen ? static_cast<int>(screen.visibleFrame.size.width) : 0;
}

int DisplayMetrics::GetVisibleHeight() {
    NSScreen* screen = [NSScreen mainScreen];
    return screen ? static_cast<int>(screen.visibleFrame.size.height) : 0;
}

float DisplayMetrics::GetScaleFactor() {
    NSScreen* screen = [NSScreen mainScreen];
    return screen ? screen.backingScaleFactor : 0;
}

std::string DisplayMetrics::GetDisplayID() {
    NSScreen* screen = [NSScreen mainScreen];
    NSString* name = [screen localizedName];
    return name ? [name UTF8String] : "Unknown Display";
}
} // namespace Display

} // namespace Engine

