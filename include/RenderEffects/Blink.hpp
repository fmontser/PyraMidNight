#pragma once
#include "RenderEffect.hpp"

namespace pyramidnight {
	class Blink : public RenderEffect {
		public:
			Blink(float duration, float lapse, const std::shared_ptr<sf::Transformable>& drawable);
			void Update();

			float Lapse;
		private:
			bool  mVisible;
			float mElapsedTime;
			std::shared_ptr<sf::Transformable> mTransformable;
	};
}