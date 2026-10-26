//
//  Window.h
//  MyTool
//
//  Created by Gulyás Péter István on 2026. 10. 25..
//

#pragma once

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

    static Window& Get() { return *s_Instance; }

    bool ShouldClose() const;
    void PollEvents();
    void SetBackgroundColor(const Color& color);

    void SetResizable(bool resizable);
    void SetClosable(bool closable);
    void SetMiniaturizable(bool miniaturizable);

    bool IsResizable() const;
    bool IsClosable() const;
    bool IsMiniaturizable() const;

    int GetWindowWidth() const;
    int GetWindowHeight() const;
    
    bool SetIcon(const std::string filepath);

private:    
    struct Impl;
    std::unique_ptr<Impl> m_Impl;
    static inline Window* s_Instance = nullptr;
};

} // namespace Engine
