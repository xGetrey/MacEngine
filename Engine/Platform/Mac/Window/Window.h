//
//  Window.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 25..
//

#include <string>
#include <memory>
#include "../Color.h"

namespace Engine {

class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    Window(Window&&) noexcept;
    Window& operator=(Window&&) noexcept;

    bool ShouldClose() const;
    void PollEvents();
    void SetBackgroundColor(const Color& color);

private:
    struct Impl;
    std::unique_ptr<Impl> m_Impl;
};

} // namespace Engine
