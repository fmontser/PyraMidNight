#include "Blink.hpp"
#include "RenderManager.hpp"

namespace pyramidnight {

	Blink::Blink(float duration, float lapse, const std::shared_ptr<sf::Transformable>& transformable) :
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
			mVisible ? mTransformable->setScale({1, 1}) : mTransformable->setScale({0, 0});
			mElapsedTime = 0.0f;
		}
		if ((!mLoop && mDuration <= 0.0f) || mTransformable.use_count() == 1)
			Disposable = true;
	}
}