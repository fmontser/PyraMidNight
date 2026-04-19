#pragma once
#include "RenderEffect.hpp"

namespace pyramidnight {
	class BreathColor : public RenderEffect {
		public:
			// colored outline breath effect (cannot be white)
			BreathColor(float duration, float lapse, sf::Color breath, sf::Color original,
				const std::weak_ptr<sf::Sprite>& sprite);
			void Update(const Context& context);
			
			float Lapse;
			
		private:
			bool                      mBreathing;
			float                     mElapsedTime;
			std::weak_ptr<sf::Sprite> mSprite;
			sf::Color                 mBreathColor;
			sf::Color                 mOriginalColor;
	};
}