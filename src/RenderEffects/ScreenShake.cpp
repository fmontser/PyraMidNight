#include <stdexcept>
#include "ScreenShake.hpp"
#include <SFML/Graphics.hpp>

namespace pyramidnight {
	
	ScreenShake::ScreenShake(float duration, float power) : RenderEffect(duration) {
		Power = power;
		mIsOriginSet = false;
	}

	void ScreenShake::Update(const Context& context) {
		if (!mIsOriginSet) {
			mViewOrigin = context.window.getView().getCenter();
			mIsOriginSet = true;
		}
		auto view = context.window.getView();

		if (!mIsShaking && mDuration > 0.0f)
			mIsShaking = true;
		if (mDuration > 0.0f) {
			mDuration -= context.deltaTime.asSeconds();
			float offsetX = ((float)rand() / RAND_MAX * 2.f - 1.f) * Power;
			float offsetY = ((float)rand() / RAND_MAX * 2.f - 1.f) * Power;
			view.setCenter({mViewOrigin.x + offsetX, mViewOrigin.y + offsetY});
		}
		if (mIsShaking && mDuration <= 0.0f) {
			view.setCenter(mViewOrigin);
			mIsShaking = false;
			Disposable = true;
		}
		context.window.setView(view);
	}

	void ScreenShake::Log(const std::string &msg) {
		(void)msg;
		//TODO log system
	}
}