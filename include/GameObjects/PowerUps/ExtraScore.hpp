#pragma once
#include "PowerUp.hpp"
#include <functional>

namespace pyramidnight {

	class ExtraScore : public PowerUp {
		public:
			ExtraScore(const sf::Texture& texture, uint32_t scoreMod);
			ICollidable::Info OnCollision(ICollidable &collider);

		private:
			int32_t mScoreMod;
	};
}