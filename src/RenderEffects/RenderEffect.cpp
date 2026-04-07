#include "RenderEffect.hpp"

namespace pyramidnight {
	
	RenderEffect::RenderEffect(float durationSeconds) {
		Disposable = false;
		mDuration = durationSeconds;
		mDuration == -1.0f ? mLoop = true : mLoop = false;
	}
}

