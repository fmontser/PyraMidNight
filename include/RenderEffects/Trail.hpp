#pragma once
#include "RenderEffect.hpp"


namespace pyramidnight {
	class Trail : public RenderEffect {
		public:
			// colored trail effect (cannot be white)
			Trail(float duration, float lapse, sf::Color trail,
				std::weak_ptr<sf::Sprite> sprite);

			void Update(const Context& context);

			float Lapse;
			
		private:
			bool                                        mTrailing;
			float                                       mElapsedTime;
			std::weak_ptr<sf::Sprite>                   mSprite;
			std::vector<std::shared_ptr<sf::Drawable>>  mDrawableVector;
			std::vector<std::shared_ptr<sf::Sprite>>    mTrails;
			sf::Color                                   mTrailColor;

			void Draw(const Context& context);
			void Clean();
			void MoveForward(std::shared_ptr<sf::Sprite> sprite);
	};
}