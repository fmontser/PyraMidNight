#include "Blink.hpp"

namespace pyramidnight {

	Blink::Blink(float duration, float lapse, const std::weak_ptr<sf::Transformable>& transformable) :
		RenderEffect(duration) ,mTransformable(transformable) {
			Lapse = lapse;
			mVisible = false;
			mElapsedTime = 0.0f;
	}

	void Blink::Update(const Context& context) {
		mElapsedTime += context.deltaTime.asSeconds();
		mDuration -= context.deltaTime.asSeconds();
		if (mElapsedTime >= Lapse) {
			mVisible = !mVisible;
			auto obj = mTransformable.lock();
			mVisible ? obj->setScale({1, 1}) : obj->setScale({0, 0});
			mElapsedTime = 0.0f;
		}
		if ((!mLoop && mDuration <= 0.0f) || mTransformable.use_count() == 0) {
			Disposable = true;
		}
	}
	
	void Blink::Log(const std::string &msg) {
		(void)msg;
		//TODO log system
	}
}