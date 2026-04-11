#pragma once
#include <functional>
#include <SFML/System/Angle.hpp>
#include "PowerUp.hpp"

namespace pyramidnight {

	class ExtraCreditPuP : public PowerUp {
		public:
			ExtraCreditPuP(const sf::Texture& texture);

			void Update(const sf::Time &deltaTime) override;
			ICollidable::Info OnCollision(ICollidable &collider);

			void ApplyCurvedMovement(const sf::Time &deltaTime);
			void EnableFlashEffect();
		private:
			float mDeltaX;
			float mDeltaY;

			void GenerateDirection();
	};
}