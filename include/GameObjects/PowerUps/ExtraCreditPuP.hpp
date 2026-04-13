#pragma once
#include <functional>
#include <SFML/System/Angle.hpp>
#include "PowerUp.hpp"

namespace pyramidnight {

	class ExtraCreditPuP : public PowerUp {
		public:
			ExtraCreditPuP(const sf::Texture& texture);
		
			void Update(const sf::Time &deltaTime) override;
		
			ICollidable::Info OnCollision(ICollidable &collider) override;
				

			private:
			float         mAnimationDelta;
			sf::IntRect   mAnimationRect;
			sf::IntRect   mSpriteRect;
			sf::Vector2u  mTextureSize;
			float         mDeltaX;
			float         mDeltaY;
			bool          mFlashEnabled;
			
			void EnableFlashEffect();
			void GenerateDirection();
			void AnimateFrame(const sf::Time &deltaTime);
			void ApplyCurvedMovement(const sf::Time &deltaTime);

	};
}