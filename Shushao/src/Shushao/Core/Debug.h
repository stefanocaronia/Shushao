#pragma once

#include "Logger.h"

namespace Shushao {

    enum class GridMode
    {
        ORTHOGRAFIC,
        PERSPECTIVE
    };

    class Debug
    {
    public:
        static void Initialize();

        static bool enabled;
        static bool infoEnabled;
        static bool gridEnabled;
        static bool drawTransforms;
        static bool drawRectTransforms;
        static GridMode debugGridMode;
        static DebugLevel level;
        static Logger Log;

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return coreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return clientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> coreLogger;
        static std::shared_ptr<spdlog::logger> clientLogger;
    };

}  // Shushao

// Core log macros
#define DEBUG_CORE_TRACE(...) ::Shushao::Debug::GetCoreLogger()->trace(__VA_ARGS__)
#define DEBUG_CORE_INFO(...) ::Shushao::Debug::GetCoreLogger()->info(__VA_ARGS__)
#define DEBUG_CORE_WARN(...) ::Shushao::Debug::GetCoreLogger()->warn(__VA_ARGS__)
#define DEBUG_CORE_ERROR(...) ::Shushao::Debug::GetCoreLogger()->error(__VA_ARGS__)

// Client log macros
#define DEBUG_TRACE(...) ::Shushao::Debug::GetClientLogger()->trace(__VA_ARGS__)
#define DEBUG_INFO(...) ::Shushao::Debug::GetClientLogger()->info(__VA_ARGS__)
#define DEBUG_WARN(...) ::Shushao::Debug::GetClientLogger()->warn(__VA_ARGS__)
#define DEBUG_ERROR(...) ::Shushao::Debug::GetClientLogger()->error(__VA_ARGS__)
