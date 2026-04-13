#pragma once
#include <SFML/Graphics/Texture.hpp>
#include "ICollidable.hpp"
#include "Common.hpp"

namespace pyramidnight {

	class Bumper : public sf::Sprite , public ICollidable, public std::enable_shared_from_this<Bumper> {
		public:
			Bumper(const sf::Texture& texture);

			Info OnCollision(ICollidable& collider) override;
			std::optional<sf::Vector2f> GetCollisionPoint(const sf::FloatRect &rect);
			void Move(int8_t magnitude, sf::Time &deltaTime, bool fine, bool coarse);
			void EnablePenaltyFlashEffect(float duration);
			void SetSpeedPenalty(float speed);

		private:
			float mSpeed;
			float mSpeedPenalty;
	};

}
