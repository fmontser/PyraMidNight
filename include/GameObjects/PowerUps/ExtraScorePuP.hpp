#pragma once
#include "PowerUp.hpp"
#include <functional>

namespace pyramidnight {

	class ExtraScorePuP : public PowerUp {
		public:
			ExtraScorePuP(const sf::Texture& texture, uint32_t scoreMod);
			ICollidable::Info OnCollision(ICollidable &collider);

		private:
			int32_t mScoreMod;
	};
}