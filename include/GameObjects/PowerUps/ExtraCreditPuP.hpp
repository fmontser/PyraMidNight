#pragma once
#include <functional>
#include <SFML/System/Angle.hpp>
#include "PowerUp.hpp"

namespace pyramidnight {

	class ExtraCreditPuP : public PowerUp {
		public:
			ExtraCreditPuP(const sf::Texture& texture);
			ICollidable::Info OnCollision(ICollidable &collider);

			void EnableFlashEffect();
	};
}