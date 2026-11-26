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

float DisplayMetricsImpl::GetDisplayHz() {
    NSScreen* screen = [NSScreen mainScreen];
    
    if (@available(macOS 12.0, *)) {
        NSInteger maxFPS = screen.maximumFramesPerSecond;
        return static_cast<float>(maxFPS);
    }
    
    NSDictionary* description = [screen deviceDescription];
    NSNumber* screenNumber = [description objectForKey:@"NSScreenNumber"];
    if (screenNumber) {
        CGDirectDisplayID displayID = [screenNumber unsignedIntValue];
        CGDisplayModeRef mode = CGDisplayCopyDisplayMode(displayID);
        if (mode) {
            double rate = CGDisplayModeGetRefreshRate(mode);
            CGDisplayModeRelease(mode);
            if (rate > 0.0) {
                return static_cast<float>(rate);
            }
        }
    }
    return 60.0;
}

bool DisplayMetricsImpl::isHDRSupported() {
    NSScreen* screen = [NSScreen mainScreen];
    return screen.maximumPotentialExtendedDynamicRangeColorComponentValue > 1.0;
}

}

