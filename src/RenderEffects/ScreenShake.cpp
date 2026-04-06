#include "ScreenShake.hpp"
#include "RenderManager.hpp"

namespace pyramidnight {
	
	ScreenShake::ScreenShake(float duration, float power) : RenderEffect(duration) {
		Power = power;
		mViewOrigin = RenderManager::GetWindow().getView().getCenter();
	}

	void ScreenShake::Update() {
		auto& window = RenderManager::GetWindow();
		auto  deltaTime = RenderManager::GetDeltaTime();
		auto  view = window.getView();

		if (!mIsShaking && mDuration > 0.0f)
			mIsShaking = true;
		if (mDuration > 0.0f) {
			mDuration -= deltaTime.asSeconds();
			float offsetX = ((float)rand() / RAND_MAX * 2.f - 1.f) * Power;
			float offsetY = ((float)rand() / RAND_MAX * 2.f - 1.f) * Power;
			view.setCenter({mViewOrigin.x + offsetX, mViewOrigin.y + offsetY});
		}
		if (mIsShaking && mDuration <= 0.0f) {
			view.setCenter(mViewOrigin);
			mIsShaking = false;
			Disposable = true;
		}
		window.setView(view);
	}
}