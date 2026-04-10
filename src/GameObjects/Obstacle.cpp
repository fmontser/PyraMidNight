#include "Obstacle.hpp"
#include "Ball.hpp"

namespace pyramidnight {

	Obstacle::Obstacle(const sf::Texture &texture) : sf::Sprite(texture) {}

	ICollidable::Info Obstacle::OnCollision(ICollidable &collider) { 
		if (collider.CollidableType == ICollidable::Type::OBSTACLE) {
			auto& ball = static_cast<Ball&>(collider);
			auto cpos = ball.GetCollisionPoint(getGlobalBounds());
			if (cpos != std::nullopt) {
				ball.Bounce(*this);
			}
		}
		return {CollidableType, false, 0, std::nullopt };
	}
}
