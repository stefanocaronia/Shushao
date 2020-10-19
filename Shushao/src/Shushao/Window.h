#pragma once

#include "Events/Event.h"

namespace se {

struct WindowProperties {
    std::string Title;
    unsigned int Width;
    unsigned int Height;
    bool Fullscreen;

    WindowProperties(const std::string& title = "Shushao Engine", unsigned int width = 1280, unsigned int height = 720, bool fullscreen = true)
        : Title(title), Width(width), Height(height), Fullscreen(fullscreen) {}
};

// Interface
class Window {
public:
    using CallbackFunction = std::function<void(Event&)>;

    static Window* Create(const WindowProperties& props = WindowProperties());
    virtual ~Window() {}

    virtual std::string GetTitle() const = 0;
    virtual unsigned int GetWidth() const = 0;
    virtual unsigned int GetHeight() const = 0;
    virtual void SetWidth(unsigned int _width) = 0;
    virtual void SetHeight(unsigned int _height) = 0;
    virtual float GetAspect() const = 0;
    virtual glm::vec2 GetViewport() const = 0;

    virtual int GetDesktopWidth() const = 0;
    virtual int GetDesktopHeight() const = 0;

    virtual void SetEventCallback(const CallbackFunction& Callback) = 0;
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

    CallbackFunction Callback;

    unsigned int width;
    unsigned int height;

protected:
    virtual void initialize(const WindowProperties& props) = 0;
    virtual void shutdown() const = 0;

    unsigned int desktopWidth;
    unsigned int desktopHeight;

    std::string title;
    bool vSync;
    bool fullscreen;
};

}  // namespace se
