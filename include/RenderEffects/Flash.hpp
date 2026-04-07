#pragma once
#include "RenderEffect.hpp"

namespace pyramidnight {
	class Flash : public RenderEffect {
		public:
			Flash(float duration, float lapse, sf::Color flash, sf::Color original,
				const std::weak_ptr<sf::Sprite>& sprite);
			void Update(const Context& context);
			void Log(const std::string& msg) override;

			float Lapse;
			
		private:
			bool                      mFlashing;
			float                     mElapsedTime;
			std::weak_ptr<sf::Sprite> mSprite;
			sf::Color                 mFlashColor;
			sf::Color                 mOriginalColor;
	};
}