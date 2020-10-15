#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace se {

struct WindowProps {
    std::string Title;
    unsigned int Width;
    unsigned int Height;
    bool Fullscreen;

    WindowProps(const std::string& title = "Shushao Engine", unsigned int width = 1280, unsigned int height = 720, bool fullscreen = true)
        : Title(title), Width(width), Height(height), Fullscreen(fullscreen) {}
};

// Interface representing a desktop system based Window
class Window {
public:
    using EventCallbackFn = std::function<void(Event&)>;

    virtual ~Window() {}

    virtual unsigned int GetWidth() const = 0;
    virtual unsigned int GetHeight() const = 0;
    virtual float GetAspect() const = 0;
    virtual glm::vec2 GetViewport() const = 0;

    inline unsigned int GetDesktopWidth() const { return desktopWidth; }
    inline unsigned int GetDesktopHeight() const { return desktopHeight; }

    virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
    virtual void SetVSync(bool enabled) = 0;
    virtual bool IsVSync() const = 0;
    virtual void Clear() const = 0;
    virtual void Clear(float, float, float, float, float) const = 0;
    virtual void SetFullscreen(bool) = 0;
    virtual void ToggleFullscreen() = 0;
    virtual void Swap() const = 0;
    virtual void Reset() const = 0;
    virtual void Update() const = 0;
    virtual void* GetNativeWindow() const = 0;

    static Window* Create(const WindowProps& props = WindowProps());

    bool fullscreen;

protected:
    virtual void initialize(const WindowProps& props) = 0;
    virtual void shutdown() const = 0;

    unsigned int desktopWidth;
    unsigned int desktopHeight;
};

}  // namespace se
