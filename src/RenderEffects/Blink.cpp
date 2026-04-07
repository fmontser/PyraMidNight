#include "Blink.hpp"

namespace pyramidnight {

	Blink::Blink(float duration, float lapse, const std::weak_ptr<sf::Transformable>& transformable) :
		RenderEffect(duration) ,mTransformable(transformable) {
			Lapse = lapse;
			mVisible = false;
			mElapsedTime = 0.0f;
	}

	void Blink::Update(const Context& context) {
		auto obj = mTransformable.lock();
		if (!obj) {
			Disposable = true;
			return;
		}

		mElapsedTime += context.deltaTime.asSeconds();
		mDuration -= context.deltaTime.asSeconds();
		if ((!mLoop && mDuration <= 0.0f) || mTransformable.use_count() == 0) {
			obj->setScale({1, 1});
			Disposable = true;
			return;
		}

		if (mElapsedTime >= Lapse) {
			mVisible = !mVisible;
			obj->setScale(mVisible ? sf::Vector2f({1, 1}) : sf::Vector2f({0, 0}));
			mElapsedTime = 0.0f;
		}
	}
	
	void Blink::Log(const std::string &msg) {
		(void)msg;
		//TODO log system
	}
}