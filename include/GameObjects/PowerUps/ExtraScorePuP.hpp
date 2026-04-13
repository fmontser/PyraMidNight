#pragma once
#include <functional>
#include <SFML/System/Angle.hpp>
#include "PowerUp.hpp"

namespace pyramidnight {

	class ExtraScorePuP : public PowerUp {
		public:
			ExtraScorePuP(const sf::Texture& texture, uint32_t scoreMod);

			void Update(const sf::Time &deltaTime) override;

			ICollidable::Info OnCollision(ICollidable &collider) override;

			
		private:
			int32_t     mScoreMod;
			float       mRotation;
			bool        mFlashEnabled;

			void EnableFlashEffect();
		};
}