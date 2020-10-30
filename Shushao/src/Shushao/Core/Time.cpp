#include "sepch.h"

#include "Time.h"

// TODO: problema chrono

namespace Shushao {

	float Time::GetTime() {
		using namespace std::chrono;
		return (float)duration_cast<milliseconds>(high_resolution_clock::now() - startTime).count() / 1000.f;
	}

	void Time::SetFrameRateLimit(float fr) {
		FrameRateLimit = fr;
		FrameLimitDuration = 1.f / FrameRateLimit;
	}

	void Time::SetFixedRateLimit(float fr) {
		FixedRateLimit = fr;
		FixedLimitDuration = 1.f / FixedRateLimit;
	}

	void Time::Update() {
		RealtimeSinceStartup = GetTime();
		Delta = RealtimeSinceStartup - Elapsed;
		Elapsed = RealtimeSinceStartup;
		FixedDeltaTime = RealtimeSinceStartup - FixedTime;
		RenderDeltaTime = RealtimeSinceStartup - RenderTime;
		FrameRate = 1.0f / Delta;
	}

	std::string Time::Clock() {
		using namespace std::chrono;
		int mil = (int)duration_cast<milliseconds>(high_resolution_clock::now() - startTime).count();

		int mills = (int)(mil % 1000);
		int seconds = (int)(mil / 1000) % 60;
		int minutes = (int)((mil / (1000 * 60)) % 60);
		//int hours   = (int) ((mil / (1000*60*60)) % 24);

		std::ostringstream clock;

		// clock << Utility::zerofill(hours, 2) << ":" << Utility::zerofill(minutes, 2) << ":" << Utility::zerofill(seconds, 2)<< "." << Utility::zerofill(mills, 3);
		clock << Utility::zerofill(minutes, 2) << ":" << Utility::zerofill(seconds, 2) << "." << Utility::zerofill(mills, 3);

		return clock.str();
	}

	// static members definitions
	float Time::Delta = 0.0f;
	float Time::FixedDeltaTime = 0.0f;
	float Time::RenderDeltaTime = 0.0f;
	float Time::FixedTime = 0.0f;
	float Time::FrameCount = 0.0f;
	float Time::FrameRate = 0.0f;
	float Time::RenderTime = 0.0f;
	float Time::Elapsed = 0.0f;
	float Time::RealtimeSinceStartup = 0.0f;
	bool Time::InFixedTimeStep = false;
	std::chrono::steady_clock::time_point Time::startTime = std::chrono::high_resolution_clock::now();

	// from Config
	float Time::FixedRateLimit = Config::Time::fixedRateLimit;
	float Time::FixedLimitDuration = 1.0f / Config::Time::fixedRateLimit;
	float Time::FrameRateLimit = Config::Time::frameRateLimit;
	float Time::FrameLimitDuration = 1.0f / Config::Time::frameRateLimit;
}  // Shushao
