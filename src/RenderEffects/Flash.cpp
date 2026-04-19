#include "Flash.hpp"

namespace pyramidnight {

	Flash::Flash(float duration, float lapse, sf::Color flash, sf::Color original,
		const std::weak_ptr<sf::Sprite>& sprite) :
			RenderEffect(duration) , mSprite(sprite) {
				Lapse = lapse;
				mElapsedTime = 0.0f;
				mFlashing = false;
				mFlashColor = flash;
				mOriginalColor = original;
			
	}

	void Flash::Update(const Context& context) {
		auto obj = mSprite.lock();
		if (!obj) {
			Disposable = true;
			return;
		}

		mElapsedTime += context.deltaTime.asSeconds();
		mDuration -= context.deltaTime.asSeconds();
		if (!mLoop && mDuration <= 0.0f) {
			obj->setColor(mOriginalColor);
			Disposable = true;
			return;
		}

		if (mElapsedTime >= Lapse) {
			mFlashing = !mFlashing;
			obj->setColor(mFlashing ? mFlashColor : mOriginalColor);
			mElapsedTime = 0.0f;
		}
	}
}