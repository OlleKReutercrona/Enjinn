#pragma once
#include <chrono>

namespace Enj {
	class Timer {
	public:
		Timer();
		Timer(const Timer& timer) = delete;
		Timer& operator=(const Timer& timer) = delete;

		void Update();

		float DeltaTime() const;
		float TotalTime() const;
		unsigned int Fps() const;
	private:
		std::chrono::high_resolution_clock::time_point mCurrentFrameTime;
		std::chrono::high_resolution_clock::time_point mLastFrameTime;
		std::chrono::duration<float> mDeltaTime;
		std::chrono::duration<double> mTotalTime;
		unsigned int mFps;
	};
}