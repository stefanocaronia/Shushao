#pragma once

#include "Config.h"

namespace Shushao {

    class Time
    {
    public:
        static float Delta;
        static float FixedDeltaTime;
        static float FixedTime;
        static float FrameCount;
        static bool InFixedTimeStep;
        static float RealtimeSinceStartup;
        static float Elapsed;

        static float FrameRateLimit;
        static float FixedRateLimit;
        static float RenderTime;
        static float FrameRate;
        static float RenderDeltaTime;
        static float FrameLimitDuration;
        static float FixedLimitDuration;

        static void SetFrameRateLimit(float);
        static void SetFixedRateLimit(float);

        static float GetTime();
        static void Update();
        static std::string Clock();

    private:
        static std::chrono::steady_clock::time_point startTime;
    };

}  // Shushao
