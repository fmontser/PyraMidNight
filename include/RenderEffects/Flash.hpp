#pragma once
#include "RenderEffect.hpp"

namespace pyramidnight {
	class Flash : public RenderEffect {
		public:
			// colored flash effect (cannot be white)
			Flash(float duration, float lapse, sf::Color flash, sf::Color original,
				const std::weak_ptr<sf::Sprite>& sprite);
			void Update(const Context& context);
			

			float Lapse;
			
		private:
			bool                      mFlashing;
			float                     mElapsedTime;
			std::weak_ptr<sf::Sprite> mSprite;
			sf::Color                 mFlashColor;
			sf::Color                 mOriginalColor;
	};
}