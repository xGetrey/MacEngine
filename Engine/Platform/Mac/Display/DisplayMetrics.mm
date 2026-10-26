//
//  DisplayMetrics.mm
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 26..
//

#import "DisplayMetrics.h"
#import <Cocoa/Cocoa.h>
#include <string>

namespace Engine::Detail {

int DisplayMetricsImpl::GetWidth() {
    NSScreen* screen = [NSScreen mainScreen];
    return screen ? static_cast<int>(screen.frame.size.width) : 0;
}

int DisplayMetricsImpl::GetHeight() {
    NSScreen* screen = [NSScreen mainScreen];
    return screen ? static_cast<int>(screen.frame.size.height) : 0;
}

int DisplayMetricsImpl::GetVisibleWidth() {
    NSScreen* screen = [NSScreen mainScreen];
    return screen ? static_cast<int>(screen.visibleFrame.size.width) : 0;
}

int DisplayMetricsImpl::GetVisibleHeight() {
    NSScreen* screen = [NSScreen mainScreen];
    return screen ? static_cast<int>(screen.visibleFrame.size.height) : 0;
}

float DisplayMetricsImpl::GetScaleFactor() {
    NSScreen* screen = [NSScreen mainScreen];
    return screen ? screen.backingScaleFactor : 0;
}

std::string DisplayMetricsImpl::GetDisplayID() {
    NSScreen* screen = [NSScreen mainScreen];
    NSString* name = [screen localizedName];
    return name ? [name UTF8String] : "Unknown Display";
}

} // namespace Engine

