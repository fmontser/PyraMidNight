#include <algorithm>
#include "Trail.hpp"
#include "Common.hpp"

namespace pyramidnight {

	Trail::Trail(float duration, float lapse, sf::Color trail, std::weak_ptr<sf::Sprite> sprite,
				std::vector<std::shared_ptr<sf::Drawable>> drawableVector) :
			RenderEffect(duration) , mSprite(sprite), mDrawableVector(drawableVector) {
				Lapse = lapse;
				mElapsedTime = 0.0f;
				mTrailColor = trail;
	}

	void Trail::Update(const Context& context) {
		auto obj = mSprite.lock();
		if (!obj) {
			Disposable = true;
			Clean();
			return;
		}

		mElapsedTime += context.deltaTime.asSeconds();
		mDuration -= context.deltaTime.asSeconds();
		if (!mLoop && mDuration <= 0.0f) {
			Disposable = true;
			Clean();
			return;
		}

		if (mElapsedTime >= Lapse) {
			auto trail = std::make_shared<sf::Sprite>(*obj);
			trail->setColor(mTrailColor);
			mTrails.push_back(trail); 
			mDrawableVector.push_back(trail);

			auto trailsCpy = mTrails;
			for (auto& trail : trailsCpy) {
				auto color = trail->getColor();
				auto scale = trail->getScale();

				color.a *= EFF_TRAIL_ALPHA_MOD;
				scale.x *= EFF_TRAIL_SCALE_MOD;
				scale.y *= EFF_TRAIL_SCALE_MOD;
				trail->setColor(color);
				trail->setScale(scale);
				
				// clean
				if (color.a < 1) {
					auto itDrawable = std::find(mDrawableVector.begin(), mDrawableVector.end(),
						std::static_pointer_cast<sf::Drawable>(trail));
					if (itDrawable != mDrawableVector.end())
						mDrawableVector.erase(itDrawable);

					auto itTrail= std::find(mTrails.begin(), mTrails.end(), trail);
					if (itTrail != mTrails.end())
						mTrails.erase(itTrail);
				}
			}
			mElapsedTime = 0.0f;
		}
		MoveForward(obj);
	}
	void Trail::Clean() {
		for (const auto& drawable : mTrails) {
			auto it = std::find(mDrawableVector.begin(), mDrawableVector.end(), drawable);
			if (it != mDrawableVector.end())
				mDrawableVector.erase(it);
		}
	}

	void Trail::MoveForward(std::shared_ptr<sf::Sprite> sprite) {
		auto it = std::find(mDrawableVector.begin(), mDrawableVector.end(), sprite);
		if (it != mDrawableVector.end()) {
			std::rotate(it, it + 1, mDrawableVector.end());
		}
	}

}