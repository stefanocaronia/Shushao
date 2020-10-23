#pragma once

namespace Shushao {

    enum class RendererAPI
    {
        None = 0,
        OpenGL = 1
    };

    class Renderer
    {
    public:
        inline static RendererAPI GetAPI() { return API; }
        inline static void SetAPI(RendererAPI _rendererAPI) { API = _rendererAPI; };

    private:
        static RendererAPI API;
    };
}