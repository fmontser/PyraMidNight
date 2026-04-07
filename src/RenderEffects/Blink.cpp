#include "Blink.hpp"
#include "RenderManager.hpp"

#include <iostream>

namespace pyramidnight {

	Blink::Blink(float duration, float lapse, const std::weak_ptr<sf::Transformable>& transformable) :
		RenderEffect(duration) ,mTransformable(transformable) {
			Lapse = lapse;
			mVisible = false;
			mElapsedTime = 0.0f;
	}

	void Blink::Update() {
		auto deltaTime = RenderManager::GetDeltaTime().asSeconds();
		
		mElapsedTime += deltaTime;
		mDuration -= deltaTime;
		if (mElapsedTime >= Lapse) {
			mVisible = !mVisible;
			auto obj = mTransformable.lock();
			mVisible ? obj->setScale({1, 1}) : obj->setScale({0, 0});
			mElapsedTime = 0.0f;
		}
		if ((!mLoop && mDuration <= 0.0f) || mTransformable.use_count() == 0) {
			std::cout << "Disposed!\n";
			Disposable = true;
		}
	}
}