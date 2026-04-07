#pragma once
#include "RenderEffect.hpp"

namespace pyramidnight {
	class Blink : public RenderEffect {
		public:
			Blink(float duration, float lapse, const std::weak_ptr<sf::Transformable>& drawable);
			void Update(const Context& context);
			void Log(const std::string& msg) override;

			float Lapse;
		private:
			bool  mVisible;
			float mElapsedTime;
			std::weak_ptr<sf::Transformable> mTransformable;
	};
}