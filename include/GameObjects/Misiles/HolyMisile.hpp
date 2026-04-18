#pragma once
#include <functional>
#include <SFML/System/Angle.hpp>
#include <optional>
#include "Misile.hpp"

namespace pyramidnight {

	class HolyMisile : public Misile {
		public:
			HolyMisile(const sf::Texture& texture);

			void Update(const sf::Time &deltaTime) override;

			ICollidable::Info OnCollision(ICollidable &collider) override;
			
		private:
			bool          mFlashEnabled;
			bool          mIsDestroyed;
			float         mAnimationDelta;
			sf::IntRect   mAnimationRect;
			sf::IntRect   mSpriteRect;
			sf::Vector2u  mTextureSize;

			void AnimateFrame(const sf::Time &deltaTime);
			void EnableFlashEffect();
		};
}