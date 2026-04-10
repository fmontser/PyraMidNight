#pragma once
#include <functional>
#include <SFML/System/Angle.hpp>
#include "PowerUp.hpp"

namespace pyramidnight {

	class ExtraScorePuP : public PowerUp {
		public:
			ExtraScorePuP(const sf::Texture& texture, uint32_t scoreMod);
			ICollidable::Info OnCollision(ICollidable &collider);

			void EnableFlashEffect();

		private:
			int32_t     mScoreMod;
			float       mRotation;
	};
}