#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Shushao/Config.h"
#include "Shushao/Window.h"

namespace se {

class WindowsWindow : public Window {
public:
    WindowsWindow(const WindowProps& props);
    virtual ~WindowsWindow();

    void Update() override;

    inline unsigned int GetWidth() const override { return data.Width; }
    inline unsigned int GetHeight() const override { return data.Height; }

    inline float GetAspect() const override { return (float)data.Width / (float)data.Height; }
    inline glm::vec2 GetViewport() const { return { (float)data.Width / (Config::pixelPerUnit / 2), (float)data.Height / (Config::pixelPerUnit / 2) }; }

    // Window attributes
    inline void SetEventCallback(const EventCallbackFn& callback) override { data.EventCallback = callback; }
    void SetVSync(bool enabled) override;
    bool IsVSync() const override;

    inline virtual void* GetNativeWindow() const { return window; }

    virtual void Clear() const override;
    virtual void Clear(float, float, float, float, float) const override;
    virtual void SetFullscreen(bool) override;
    virtual void ToggleFullscreen() override;
    virtual void Swap() const override;
    virtual void Reset() const override;

private:
    virtual void Init(const WindowProps& props);
    virtual void Shutdown();

    GLFWwindow* window;

    struct WindowData {
        std::string Title;
        unsigned int Width, Height;
        bool VSync;
        bool Fullscreen;

        EventCallbackFn EventCallback;
    };

    WindowData data;
};

}  // namespace se