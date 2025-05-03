#include "Timer.h"

namespace Enj {
	Timer::Timer() :
		mCurrentFrameTime(std::chrono::high_resolution_clock::now()),
		mLastFrameTime(mCurrentFrameTime),
		mDeltaTime(std::chrono::duration<float>(0.0f)),
		mTotalTime(std::chrono::duration<double>(0.0)),
		mFps(0) {
	}

	void Timer::Update() {
		mLastFrameTime = mCurrentFrameTime;
		mCurrentFrameTime = std::chrono::high_resolution_clock::now();

		mDeltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(mCurrentFrameTime - mLastFrameTime);

		mTotalTime = mTotalTime + mDeltaTime;

		mFps = static_cast<unsigned int>(1.0f / mDeltaTime.count());
	}

	float Timer::DeltaTime() const {
		return mDeltaTime.count();
	}

	float Timer::TotalTime() const {
		return mTotalTime.count();
	}

	unsigned int Timer::Fps() const {
		return mFps;
	}

}