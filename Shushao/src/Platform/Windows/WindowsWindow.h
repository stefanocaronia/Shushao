#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Shushao/Config.h"
#include "Shushao/Window.h"

namespace se {

    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProperties& props);
        virtual ~WindowsWindow();

        inline std::string GetTitle() const override { return title; }
        inline unsigned int GetWidth() const override { return width; }
        inline unsigned int GetHeight() const override { return height; }
        void SetWidth(unsigned int _width) override { width = _width; }
        void SetHeight(unsigned int _height)     override { height = _height; }
        inline virtual void* GetNativeWindow() const override { return window; }
        inline float GetAspect() const override { return (float)width / (float)height; }
        inline glm::vec2 GetViewport() const { return { (float)width / (Config::pixelPerUnit / 2), (float)height / (Config::pixelPerUnit / 2) }; }
        inline void SetEventCallback(const CallbackFunction& callback) override { Callback = callback; }
        virtual int GetDesktopWidth()  const override { return desktopWidth; }
        virtual int GetDesktopHeight()  const override { return desktopHeight; }
        GLFWmonitor* GetMonitor()  const { return monitor; }

        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        virtual void Clear() const override;
        virtual void Clear(float, float, float, float, float) const override;
        virtual void SetFullscreen(bool) override;
        virtual void ToggleFullscreen() override;
        virtual void Swap() const override;
        virtual void Reset() const override;
        virtual void Update() const override;

    private:
        GLFWwindow* window;
        GLFWmonitor* monitor;

        virtual void initialize(const WindowProperties& props);
        virtual void shutdown() const override;

        void inizializeGLFW();
        void initializeGlad();
        void initializeOpenGL();
        void retrieveDesktopSize();
        void setGlfwCallbacks();
    };

}  // namespace se